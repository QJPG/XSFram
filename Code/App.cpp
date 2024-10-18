#include <iostream>

#include "../XSFML/XSFML.h"
#include "MainLoop.h"
#include "Environment.h"

namespace DeviceConfig {
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
            NORMAL_WINDOW       = 0x1 << 0x0,
            RESIZABLE_WINDOW    = 0x1 << 0x1,
            OPENGL_WINDOW       = 0x1 << 0x2,
            VULKAN_WINDOW       = 0x1 << 0x3,
            METAL_WINDOW        = 0x1 << 0x4,
            FLSCR_WINDOW        = 0x1 << 0x5,
            CENTER_WINDOW       = 0x1 << 0x6,
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

        int             EXITCODE = 0x0;

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
            return FLAGS & CENTER_WINDOW;
        }
    };

    void WINDOW_INIT(WNDINFO& INFO) {
        INFO.UPDATED = false;

        assert(INFO.WNDGDI != nullptr, "Error: Invalid GDI!");
        
        if (SDL_Init(SDL_INIT_EVERYTHING) < 0) throw SDL_GetError();

        Uint32 SDL_WNDFLAGS = NULL;

        if (INFO.IS_OPENGL()) {
            SDL_WNDFLAGS |= SDL_WINDOW_OPENGL;

            OpenGLGDI& OGLGDI = (OpenGLGDI&) INFO.WNDGDI;

            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,   INFO.WNDGDI->VERSION_MAJOR);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,   INFO.WNDGDI->VERSION_MINOR);
            
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,    SDL_GL_CONTEXT_PROFILE_CORE);

            SDL_GL_SetAttribute(SDL_GL_RED_SIZE,        OGLGDI.SIZE_CHANNEL_R);
            SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,      OGLGDI.SIZE_CHANNEL_G);
            SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,       OGLGDI.SIZE_CHANNEL_B);
            SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,      OGLGDI.SIZE_CHANNEL_A);
            SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,      OGLGDI.SIZE_BUFFER_DEPTH);
            SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,    OGLGDI.SIZE_BUFFER_DOUBL);
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

        assert((INFO.WINDOW != nullptr), SDL_GetError());

    }

    void WINDOW_BEGIN(WNDINFO& INFO) {
        if (INFO.IS_OPENGL()) {
            INFO.WNDGDC = SDL_GL_CreateContext((SDL_Window*) INFO.WINDOW);

            assert(INFO.WNDGDC != nullptr, SDL_GetError());
        }

        INFO.WNDGDI->DISPLAY_PROCESS = SDL_GL_GetProcAddress;
        INFO.WNDGDI->BeginGDI();

        INFO.RUNNING = true;
    }

    void WINDOW_UPDATE(WNDINFO& INFO) {
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

    void WINDOW_DESTROY(WNDINFO& INFO) {
        INFO.WNDGDI->DestroyGDI();
        INFO.WNDGDI->DISPLAY_PROCESS = NULL;

        SDL_GL_DeleteContext((SDL_GLContext) INFO.WNDGDC);
        SDL_DestroyWindow((SDL_Window*) INFO.WINDOW);
        SDL_Quit();
    }
};


const char* SOURCE = R"(

@stage (
    use: "OpenGL"
    tex: "Memory Unsafe"
)

@frames (
    target: "GBuffer"

    @ (frame: "Diffuse" tex: "2D_RGBA_RGBA16F")
    @ (frame: "Normals" tex: "2D_RGB_RGB16F")
    @ (frame: "Depth"   tex: "2D_DEPTH_DEPTH")
)

)";

int main(int argc, char * argv[]) {

    /*
    XSFML::XSFMLDocument doc;

    XSFML::XSFML_LOAD(doc, SOURCE);
    XSFML::XSFML_PARSE(doc);

    std::vector<XSFML::XSFMLBlock> blocks;
    
    //doc.GetBlocksByKeywordValue(blocks, "name", "", false);
    
    for (size_t i = 0; i < doc.blocks.size(); i++) {
        std::cout << "Block: " << doc.blocks[i].name << " Size: " << doc.blocks[i].attributes.size() << " [ID: " << doc.blocks[i]._id << " Anonymous?: " << doc.blocks[i].isAnonymous << "]" << std::endl;
        

       for (auto k = doc.blocks[i].attributes.begin(); k != doc.blocks[i].attributes.end(); k++) {
                std::cout << "\tAttribute: " << k->first << " = " << k->second << std::endl;
       }

       std::cout << "\n" << std::endl;
    }

    XSFML::XSFML_CLEAR(doc);
    */

    /*DEFAULT ENVIRONMENT VARS*/

    Environment::SET_STR_ENVVAR("WND_TITLE", "Application");
    
    Environment::SET_I32_ENVVAR("WND_SHOWX", 0);
    Environment::SET_I32_ENVVAR("WND_SHOWY", 0);

    Environment::SET_I32_ENVVAR("WND_SIZEX", 840);
    Environment::SET_I32_ENVVAR("WND_SIZEY", 600);

    Environment::SET_I32_ENVVAR("GL_MAJOR", 3);
    Environment::SET_I32_ENVVAR("GL_MINOR", 1);

    /*DEFAULT WINDOW/DISPLAY*/

    DeviceConfig::WNDINFO INFO;

    INFO.FLAGS = INFO.OPENGL_WINDOW | INFO.CENTER_WINDOW;

    Environment::GET_I32_ENVVAR("WND_SHOWX", INFO.DIM.X);
    Environment::GET_I32_ENVVAR("WND_SHOWY", INFO.DIM.Y);

    Environment::GET_I32_ENVVAR("WND_SIZEX", INFO.DIM.W);
    Environment::GET_I32_ENVVAR("WND_SIZEY", INFO.DIM.H);
    
    Environment::GET_STR_ENVVAR("WND_TITLE", INFO.TITLE);

    INFO.WNDGDI = new OpenGLGDI;

    Environment::GET_I32_ENVVAR("GL_MAJOR", (int&) INFO.WNDGDI->VERSION_MAJOR);
    Environment::GET_I32_ENVVAR("GL_MINOR", (int&) INFO.WNDGDI->VERSION_MINOR);

    DeviceConfig::WINDOW_INIT(INFO);
    DeviceConfig::WINDOW_BEGIN(INFO);
    DeviceConfig::WINDOW_UPDATE(INFO);
    DeviceConfig::WINDOW_DESTROY(INFO);

    return INFO.EXITCODE;
}