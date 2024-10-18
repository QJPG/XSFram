#pragma once

#include "GDI.h"

class OpenGLGDI : public GDI {
private:

public:
    OpenGLGDI();

    void						BeginGDI() override;
    void						RenderGDI() override;
    void						DestroyGDI() override;

    unsigned int				SIZE_CHANNEL_R = 0x8;
    unsigned int				SIZE_CHANNEL_G = 0x8;
    unsigned int				SIZE_CHANNEL_B = 0x8;
    unsigned int				SIZE_CHANNEL_A = 0x8;
    unsigned int				SIZE_BUFFER_DEPTH = 0x18;
    unsigned int				SIZE_BUFFER_DOUBL = 0x1;
};
