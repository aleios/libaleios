#include "logger.hpp"
#include <mutex>
#include <thread>
#include <iostream>
#include <cstdarg>
#include <vector>
#include <chrono>
#include <ctime>

namespace ae
{
    namespace log
    {
        namespace detail
        {
            static std::recursive_mutex s_mutex;
            VerbosityLevel g_stderrVerbosity = VerbosityLevel::INFO;
            static VerbosityLevel s_maxVerbosity = VerbosityLevel::INFO;
            static std::vector<Callback> s_callbacks;
            const auto s_start_time = std::chrono::steady_clock::now();

            thread_local std::string ts_threadName = "";

            VerbosityLevel GetVerbosityCutoff()
            {
                return g_stderrVerbosity > s_maxVerbosity ? g_stderrVerbosity : s_maxVerbosity;
            }

            void LogMessage(int sskip, const Message& msg, bool indent, bool abortOnFail)
            {
                const auto verbosity = msg.verbosity;
                std::lock_guard<std::recursive_mutex> lck(s_mutex);

                // Log to stderr
                if (verbosity <= g_stderrVerbosity)
                {
                    fprintf(stderr, "%s%s%s%s\n", msg.preamble, msg.indent, msg.prefix, msg.message);
                    fflush(stderr);
                }

                // Log to file
                for (auto& p : s_callbacks)
                {
                    if (verbosity >= p.verbosity)
                    {
                        p.callback(p.handle, msg);

                        // Flush
                        p.flush(p.handle);
                    }
                }

                // ABORT
                if (msg.verbosity == VerbosityLevel::Fatal) {
                    //flush();

                    if (abortOnFail)
                    {
                        abort();
                    }
                }
            }

            static const char* filename(const char* path)
            {
                for (auto ptr = path; *ptr; ++ptr) {
                    if (*ptr == '/' || *ptr == '\\') {
                        path = ptr + 1;
                    }
                }
                return path;
            }

            static void GenPreamble(char* out_buff, size_t out_buff_size, VerbosityLevel verbosity, const char* file, unsigned line)
            {
                long long ms_since_epoch = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
                time_t sec_since_epoch = time_t(ms_since_epoch / 1000);
                tm time_info;
#ifdef _MSC_VER
                localtime_s(&time_info, &sec_since_epoch);
#else
                localtime_r(&sec_since_epoch, &time_info);
#endif

                auto uptime_ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - s_start_time).count();
                auto uptime_sec = uptime_ms / 1000.0;

                //char thread_name[LOGURU_THREADNAME_WIDTH + 1] = { 0 };
                //get_thread_name(thread_name, LOGURU_THREADNAME_WIDTH + 1, true);

                char level_buff[6];
                if (verbosity <= VerbosityLevel::Fatal) {
                    snprintf(level_buff, sizeof(level_buff) - 1, "FATL");
                }
                else if (verbosity == VerbosityLevel::Error) {
                    snprintf(level_buff, sizeof(level_buff) - 1, "ERR");
                }
                else if (verbosity == VerbosityLevel::Warning) {
                    snprintf(level_buff, sizeof(level_buff) - 1, "WARN");
                }
                else {
                    snprintf(level_buff, sizeof(level_buff) - 1, "% 4d", verbosity);
                }

                // Clean the filename
                const char* fname = filename(file);
                unsigned int fnameSize = strlen(fname);

                //[%-*s]

                snprintf(out_buff, out_buff_size, "[%04d-%02d-%02d %02d:%02d:%02d.%03lld] (%3.3fs) %*s:%-5u %4s| ",
                    1900 + time_info.tm_year, 1 + time_info.tm_mon, time_info.tm_mday,
                    time_info.tm_hour, time_info.tm_min, time_info.tm_sec, ms_since_epoch % 1000,
                    uptime_sec,
                    fnameSize,
                    fname, line, level_buff);
            }

            void LogAll(int sskip, VerbosityLevel verbosity, const char* file, unsigned int line, const char* prefix, const char* buff)
            {
                char pbuf[128];
                GenPreamble(pbuf, sizeof(pbuf), verbosity, file, line);
                Message msg{ verbosity, file, line, pbuf, "", prefix, buff };
                LogMessage(sskip, msg, true, true);
            }

            void log(VerbosityLevel verbosity, const char* file, unsigned int line, const char* fmt, ...)
            {
                va_list vlist;
                va_start(vlist, fmt);

                std::string msg;
#ifdef _MSC_VER
                int bytes = _vscprintf(fmt, vlist);
                char* buff = new char[bytes + 1];
                vsnprintf(buff, bytes + 1, fmt, vlist);
                msg = std::string(buff);
#else
                char* buff = nullptr;
                int res = vasprintf(&buff, fmt, vlist);
                msg = std::string(buff);
#endif
                LogAll(1, verbosity, file, line, "", msg.c_str());
                va_end(vlist);
                delete[] buff;

            }

            void logAbort(int sskip, const char* expr, const char* file, unsigned int line, const char* fmt, ...)
            {
                va_list vlist;
                va_start(vlist, fmt);

                std::string msg;
#ifdef _MSC_VER
                int bytes = _vscprintf(fmt, vlist);
                char* buff = new char[bytes + 1];
                vsnprintf(buff, bytes + 1, fmt, vlist);
                msg = std::string(buff);
#else
                char* buff = nullptr;
                int res = vasprintf(&buff, fmt, vlist);
                msg = std::string(buff);
#endif
                LogAll(1, VerbosityLevel::FATAL, file, line, expr, msg.c_str());
                va_end(vlist);
                abort();
            }

            void logAbort(int sskip, const char* expr, const char* file, unsigned int line)
            {
                logAbort(sskip, expr, file, line, "");
            }

            void AddCallback(const char* id, LogHandler callback, void* handle, VerbosityLevel verbosity, FileCloseHandler close, FileFlushHandler flush)
            {
                std::lock_guard<std::recursive_mutex> lck(s_mutex);
                s_callbacks.push_back(Callback{ id, verbosity, callback, handle, close, flush });
            }

            void FileLog(void* handle, const ae::log::detail::Message& message)
            {
                FILE* file = reinterpret_cast<FILE*>(handle);
                fprintf(file, "%s%s%s%s\n", message.preamble, message.indent, message.prefix, message.message);

                fflush(file);
            }

            void FileClose(void* handle)
            {
                FILE* file = reinterpret_cast<FILE*>(handle);
                fclose(file);
            }

            void FileFlush(void* handle)
            {
                FILE* file = reinterpret_cast<FILE*>(handle);
                fflush(file);
            }
        }

        bool AddFile(const std::string& filename, FileOpt option, VerbosityLevel verbosity)
        {
            const char* openMode = (option == FileOpt::TRUNCATE) ? "w" : "a";
            auto file = fopen(filename.c_str(), openMode);

            if (!file) return false;

            detail::AddCallback(filename.c_str(), detail::FileLog, file, verbosity, detail::FileClose, detail::FileFlush);

            return true;
        }
    }
}