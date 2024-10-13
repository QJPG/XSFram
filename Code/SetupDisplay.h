#pragma once

#include <SDL.h>

#include "IncludeGraphics.h"


struct BaseDisplayContext {

private:
    bool                bdc_HasChanges;

    unsigned short      sw_Width;
    unsigned short      sw_Height;

    int                 pw_PosX;
    int                 pw_PosY;

    str                 wd_Title;
    bool                wd_EnableDebug;

public:
    GDI* ptr_GDI = NULL;

    enum WindowFlags {
        NORMAL,
        OPENGL,
        VULKAN,
        METAL,
    };

    WindowFlags flag;

    unsigned int GDI_VMinor;
    unsigned int GDI_VMajor;

    bool beginCentered;

    BaseDisplayContext() {
        flag = WindowFlags::NORMAL;

        GDI_VMinor = 0;
        GDI_VMajor = 0;

        beginCentered = true;

        bdc_HasChanges = false;

        sw_Width = 1024;
        sw_Height = 600;

        pw_PosX = 0;
        pw_PosY = 0;

        wd_Title = "";
        wd_EnableDebug = false;
    }

    ~BaseDisplayContext() {
        delete ptr_GDI;
    }

    void SetTitle(const char* title) {
        wd_Title = title;
        bdc_HasChanges = true;
    }

    void SetSize(unsigned short width, unsigned short height) {
        sw_Width = width;
        sw_Height = height;
        bdc_HasChanges = true;
    }

    bool HasChanges() const {
        return bdc_HasChanges;
    }

    void ReleaseChanges() {
        bdc_HasChanges = false;
    }

    const char* GetTitle() const {
        return wd_Title;
    }

    unsigned short GetWidth() const {
        return sw_Width;
    }

    unsigned short GetHeight() const {
        return sw_Height;
    }

    int GetPosX() const {
        return pw_PosX;
    }

    int GetPosY() const {
        return pw_PosY;
    }

    void SetPosition(int x, int y) {
        pw_PosX = x;
        pw_PosY = y;
        bdc_HasChanges = true;
    }
};

class SetupDisplay
{

public:
    enum CodeDestroyReasons {
        NORMAL_REASON,
        DISPLAY_ERROR_REASON,
        DRIVER_ERROR_REASON,
    };

    void*                               STD_PROCESS = NULL;

    SetupDisplay						();

    void InitDisplay					(BaseDisplayContext& bDisplayContext);
    //void InitGraphics					(GDI& XGDI);
    
    void UpdateDisplay					(BaseDisplayContext& bDisplayContext);
    //void UpdateGraphics					(GDI& XGDI);

    //void DestroyGraphics				(GDI& XGDI);
    void DestroyDisplay					(BaseDisplayContext& bDisplayContext);

    bool IsRequestedDestroySetup		() const;

    CodeDestroyReasons GetDestroyReason	() const;

    template	<typename T>

    static T& GetGDI			        (GDI& XGDI);

private:
    bool rq_DestroySetup;

    CodeDestroyReasons rs_DestroySetup;

    SDL_Window* ptr_SDLWindow = NULL;
    SDL_GLContext STDGLContext = NULL;
    SDL_Event SDLEvent = SDL_Event{};
};

template<typename T>
inline T& SetupDisplay::GetGDI(GDI& XGDI)
{
    return static_cast<T&>(XGDI);
}
