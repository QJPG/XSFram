#include "SetupDisplay.h"

SetupDisplay::SetupDisplay()
{
    rq_DestroySetup = false;
    rs_DestroySetup = CodeDestroyReasons::NORMAL_REASON;
}

void SetupDisplay::InitDisplay(BaseDisplayContext& bDisplayContext)
{
    if (bDisplayContext.beginCentered) {
        bDisplayContext.SetPosition(SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
        bDisplayContext.ReleaseChanges();
    }

    assert((SDL_Init(SDL_INIT_EVERYTHING) > 0, SDL_GetError()));

    Uint32 SDL_FLAGS = SDL_WINDOW_SHOWN;

    switch (bDisplayContext.flag) {
        case BaseDisplayContext::OPENGL: {
            SDL_FLAGS |= SDL_WINDOW_OPENGL;

            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, bDisplayContext.GDI_VMajor);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, bDisplayContext.GDI_VMinor);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

            SDL_GL_SetAttribute(SDL_GL_RED_SIZE,        8);
            SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,      8);
            SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,       8);
            SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,      8);
            SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,      24);
            SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,    1);

            break;
        };
    }


    ptr_SDLWindow = SDL_CreateWindow(bDisplayContext.GetTitle(),
        bDisplayContext.GetPosX(), bDisplayContext.GetPosY(),
        bDisplayContext.GetWidth(), bDisplayContext.GetHeight(), SDL_FLAGS);

    assert((ptr_SDLWindow != nullptr, SDL_GetError()));

    switch (bDisplayContext.flag) {
        case BaseDisplayContext::OPENGL: {
            STDGLContext = SDL_GL_CreateContext(ptr_SDLWindow);

            assert((STDGLContext != nullptr, SDL_GetError()));

            break;
        };
    }

    bDisplayContext.ptr_GDI->DISPLAY_PROCESS = STD_PROCESS;
    bDisplayContext.ptr_GDI->BeginGDI();
}

void SetupDisplay::UpdateDisplay(BaseDisplayContext& bDisplayContext)
{
    while (SDL_PollEvent(&SDLEvent) != 0) {
        if (SDLEvent.type == SDL_QUIT) {
            rq_DestroySetup = true;
        }
    }

   bDisplayContext.ptr_GDI->RenderGDI();

    switch (bDisplayContext.flag) {
        case BaseDisplayContext::OPENGL: {
            SDL_GL_SwapWindow(ptr_SDLWindow);

            break;
        };
    }
}

void SetupDisplay::DestroyDisplay(BaseDisplayContext& bDisplayContext)
{
    bDisplayContext.ptr_GDI->DestroyGDI();
    bDisplayContext.ptr_GDI->DISPLAY_PROCESS = NULL;

    SDL_GL_DeleteContext(STDGLContext);
    SDL_DestroyWindow(ptr_SDLWindow);
    SDL_Quit();
}

bool SetupDisplay::IsRequestedDestroySetup() const
{
    return rq_DestroySetup;
}

SetupDisplay::CodeDestroyReasons SetupDisplay::GetDestroyReason() const
{
    return rs_DestroySetup;
}
