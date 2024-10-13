#include <iostream>

#include "MainLoop.h"

namespace DVI {
    typedef const char* CSTR;

    template <typename T>
    struct COORD {
        T X = 0;
        T Y = 0;
    };
    
    template <typename T>
    struct RECT {
        T X = 0;
        T Y = 0;
        T W = 0;
        T H = 0;
    };

    struct WNDINFO {
        enum {
            NORMAL_WINDOW       = 1 << 0,
            RESIZABLE_WINDOW    = 1 << 1,
            OPENGL_WINDOW       = 1 << 2,
            VULKAN_WINDOW       = 1 << 3,
            METAL_WINDOW        = 1 << 4,
            FLSCR_WINDOW        = 1 << 5,
            CNTER_WINDOW        = 1 << 6,
        };

        unsigned int    FLAGS = NORMAL_WINDOW;

        RECT<int>       DIM;

        CSTR            TITLE = "";

        bool            UPDATED = false;    //To Update Any Changes on Window Set To TRUE

        void*           WINDOW = NULL;
        void*           WNDGDC = NULL;      //For Graphics Driver Context
        GDI*            WNDGDI = NULL;

        unsigned int    FPS = 60;

        bool            RUNNING = false;

        int             EXITCODE = 0;

        ~WNDINFO() {
            if (WNDGDI) delete WNDGDI;
        }

        bool IS_OPENGL() const {
            return FLAGS & OPENGL_WINDOW;
        }

        bool IS_VULKAN() const {
            return FLAGS & VULKAN_WINDOW;
        }

        bool IS_METAL() const {
            return FLAGS & METAL_WINDOW;
        }

        bool IS_NORMAL() const {
            return FLAGS & NORMAL_WINDOW;
        }

        bool IS_CENTERED() const {
            return FLAGS & CNTER_WINDOW;
        }
    };

    void INIT_DISPLAY(WNDINFO& INFO) {
        INFO.UPDATED = false;

        assert(INFO.WNDGDI != nullptr, "Error: Invalid GDI!");
        
        if (SDL_Init(SDL_INIT_EVERYTHING) < 0) throw SDL_GetError();

        Uint32 SDL_WNDFLAGS = NULL;

        if (INFO.IS_OPENGL()) {
            SDL_WNDFLAGS |= SDL_WINDOW_OPENGL;

            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,   INFO.WNDGDI->VERSION_MAJOR);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,   INFO.WNDGDI->VERSION_MINOR);
            
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,    SDL_GL_CONTEXT_PROFILE_CORE);

            SDL_GL_SetAttribute(SDL_GL_RED_SIZE,        8);
            SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,      8);
            SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,       8);
            SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,      8);
            SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,      24);
            SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,    1);
        }
        
        if (INFO.IS_VULKAN()) {
            SDL_WNDFLAGS |= SDL_WINDOW_VULKAN;
        }

        if (INFO.IS_METAL()) {
            SDL_WNDFLAGS |= SDL_WINDOW_METAL;
        }

        if (INFO.IS_NORMAL()) {
            SDL_WNDFLAGS |= SDL_WINDOW_SHOWN;
        }

        if      (INFO.FLAGS & INFO.RESIZABLE_WINDOW)    SDL_WNDFLAGS  |= SDL_WINDOW_RESIZABLE;
        if      (INFO.FLAGS & INFO.FLSCR_WINDOW)        SDL_WNDFLAGS  |= SDL_WINDOW_FULLSCREEN;

        if (INFO.IS_CENTERED()) {
            INFO.DIM.X = SDL_WINDOWPOS_CENTERED;
            INFO.DIM.Y = SDL_WINDOWPOS_CENTERED;
        }

        INFO.WINDOW = SDL_CreateWindow(INFO.TITLE, INFO.DIM.X, INFO.DIM.Y, INFO.DIM.W, INFO.DIM.H, SDL_WNDFLAGS);

        assert(INFO.WINDOW != nullptr, SDL_GetError());

    }

    void BEGIN_DISPLAY(WNDINFO& INFO) {
        if (INFO.IS_OPENGL()) {
            INFO.WNDGDC = SDL_GL_CreateContext((SDL_Window*) INFO.WINDOW);

            assert(INFO.WNDGDC != nullptr, SDL_GetError());
        }

        INFO.WNDGDI->DISPLAY_PROCESS = SDL_GL_GetProcAddress;
        INFO.WNDGDI->BeginGDI();

        INFO.RUNNING = true;
    }

    void UPDATE_DISPLAY(WNDINFO& INFO) {
        SDL_Event EVT;

        while (INFO.RUNNING) {
            while (SDL_PollEvent(&EVT) != 0) {
                if (EVT.type == SDL_QUIT) {
                    INFO.RUNNING = false;
                }
            }

            INFO.WNDGDI->RenderGDI();

            if (INFO.IS_OPENGL()) {
                SDL_GL_SwapWindow((SDL_Window*) INFO.WINDOW);
            }
        }
    }

    void DESTROY_DISPLAY(WNDINFO& INFO) {
        INFO.WNDGDI->DestroyGDI();
        INFO.WNDGDI->DISPLAY_PROCESS = NULL;

        SDL_GL_DeleteContext((SDL_GLContext) INFO.WNDGDC);
        SDL_DestroyWindow((SDL_Window*) INFO.WINDOW);
        SDL_Quit();
    }
};

int main(int argc, char * argv[]) {

    DVI::WNDINFO INFO;
    INFO.DIM = { 0, 0, 1024, 600 };
    INFO.FLAGS = INFO.OPENGL_WINDOW | INFO.CNTER_WINDOW;
    INFO.TITLE = "My XSFram Application";
    INFO.WNDGDI = new OpenGL_GDI;
    INFO.WNDGDI->VERSION_MAJOR = 3;
    INFO.WNDGDI->VERSION_MINOR = 1;

    DVI::INIT_DISPLAY(INFO);
    DVI::BEGIN_DISPLAY(INFO);
    DVI::UPDATE_DISPLAY(INFO);
    DVI::DESTROY_DISPLAY(INFO);

    /*enum RunDriverModes {
        NODRIVER,
        OPENGL,
    };

    RunDriverModes mode;

    BaseDisplayContext displayContext;
    SetupDisplay setupDisplay;
    MainLoop mainLoop;

    mode = RunDriverModes::OPENGL;
    
    switch (mode) {
        case RunDriverModes::NODRIVER: {
            break;
        };

        case RunDriverModes::OPENGL: {
            displayContext.flag = BaseDisplayContext::OPENGL;
            displayContext.GDI_VMinor = 1;
            displayContext.GDI_VMajor = 3;
            displayContext.ptr_GDI = new OpenGL_GDI;

            break;
        };

    };*/

    //setupDisplay.InitDisplay(displayContext);

    //mainLoop.Start(setupDisplay, displayContext);

    return INFO.EXITCODE;
}