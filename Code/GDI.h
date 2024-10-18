#pragma once

#include <glad/glad.h>
#include <unordered_map>
#include <assert.h>

#define					GDI_NAME_UNKNWN "Unknown"
#define					GDI_NAME_OPENGL "OpenGL"

typedef const char*		str;
typedef unsigned int	u32;
typedef int				i32;


class GDI
{
private:
    //unsigned short		GDI_VMinor;
    //unsigned short		GDI_VMajor;

    std::unordered_map
        <str, u32>		GDIUNAMES;

protected:
    const char*			GDI_DriverName;

public:
    unsigned int		VERSION_MINOR = 0;
    unsigned int		VERSION_MAJOR = 0;

    void*				DISPLAY_PROCESS = NULL;

                        GDI();

    virtual void		BeginGDI() = 0;
    virtual void		RenderGDI() = 0;
    virtual void		DestroyGDI() = 0;

    const char*			GetDriverName() const;

    void				SetUName(str name, u32 val);
    u32					GetUName(str name, u32 dft = 0) const;

};

