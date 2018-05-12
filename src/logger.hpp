#pragma once
#ifndef AE_LOGGER_HPP
#define AE_LOGGER_HPP

namespace ae
{
    enum class VerbosityLevel {
        Off = -4,
        Fatal = -3,
        Error = -2,
        Warning = -1,
        Info = 0
    };

    typedef VerbosityLevel LogLevel;

    namespace log
    {

        enum class FileOpt
        {
            TRUNCATE,
            APPEND
        };

        namespace detail
        {
            struct Message
            {
                VerbosityLevel verbosity;
                const char* file;
                unsigned int line;
                const char* preamble;
                const char* indent;
                const char* prefix;
                const char* message;
            };

            typedef void(*LogHandler)(void* handle, const Message& message);
            typedef void(*FileCloseHandler)(void* handle);
            typedef void(*FileFlushHandler)(void* handle);
            struct Callback
            {
                std::string id;
                VerbosityLevel verbosity;
                LogHandler callback;
                void* handle;
                FileCloseHandler close;
                FileFlushHandler flush;
            };

            VerbosityLevel GetVerbosityCutoff();
            inline void log(VerbosityLevel verbosity, const char* file, unsigned int line, const char* fmt, ...);
            inline void logAbort(int sskip, const char* expr, const char* file, unsigned int line, const char* fmt, ...);
            inline void logAbort(int sskip, const char* expr, const char* file, unsigned int line);
            void AddCallback(const char* id, LogHandler callback, void* handle, VerbosityLevel verbosity, FileCloseHandler close = nullptr, FileFlushHandler flush = nullptr);
            void LogAll(int sskip, VerbosityLevel verbosity, const char* file, unsigned int line, const char* prefix, const char* buff);
            void LogMessage(int sskip, const Message& msg, bool indent, bool abortOnFail);
        }

        bool AddFile(const std::string& filename, FileOpt option, VerbosityLevel verbosity);
    }
}
#if defined(_MSC_VER)
#define AE_LOGGER_PREDICT_FALSE(x) (x)
#define AE_LOGGER_PREDICT_TRUE(x)  (x)
#else
#define AE_LOGGER_PREDICT_FALSE(x) (__builtin_expect(x, 0))
#define AE_LOGGER_PREDICT_TRUE(x)  (__builtin_expect(!!(x), 1))
#endif

#define AE_VLOGF(verbosityLevel, ...) \
	(verbosityLevel > ae::log::detail::GetVerbosityCutoff()) ? (void)0 : ae::log::detail::log(verbosityLevel, __FILE__, __LINE__, __VA_ARGS__)
#define AE_LOGF(verbosityName, ...) AE_VLOGF(verbosityName, __VA_ARGS__)

#define AE_ABORTF(...) ae::log::detail::logAbort(0, "ABORT: ", __FILE__, __LINE__, __VA_ARGS__)

#define AE_ASSERTINFOF(condition, info, ...) AE_LOGGER_PREDICT_TRUE((condition) == true) ? (void)0 : ae::log::detail::logAbort(0, "Assertation!  " info "  ", __FILE__, __LINE__, ##__VA_ARGS__)

#define AE_ASSERTF(condition, ...) AE_ASSERTINFOF(condition, #condition, ##__VA_ARGS__)

#endif