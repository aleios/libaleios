#include "dreamcastwindow.hpp"

#include <kos.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

namespace ae
{
    namespace detail
    {
        void DreamcastWindow::CheckEvents()
        {
            // Update controllers
            static uint32_t MAX_CONTROLLERS = 4;
            for(uint32_t i = 0; i < MAX_CONTROLLERS; i++)
            {
                maple_device_t* cont = nullptr;

                if((cont = maple_enum_type(i, MAPLE_FUNC_CONTROLLER)) == nullptr)
                {
                    auto state = (cont_state_t*)maple_dev_status(cont);
                    if(state)
                    {
                        // Update controller status here.
                    }
                }
            }
            
            // Keyboard support
        }

        void DreamcastWindow::Clear()
        {
            glClear(GL_COLOR_BUFFER_BIT);
        }

        void DreamcastWindow::Display()
        {
            glutSwapBuffers();
        }

        void DreamcastWindow::Init()
        {
            glKosInit();
        }

        void DreamcastWindow::Destroy()
        {

        }
    }
}
