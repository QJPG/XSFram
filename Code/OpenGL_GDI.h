#pragma once

#include "GDI.h"

class OpenGL_GDI : public GDI {
private:

public:
	OpenGL_GDI();

	void						BeginGDI() override;
	void						RenderGDI() override;
	void						DestroyGDI() override;
};
