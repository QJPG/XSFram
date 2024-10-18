#include "OpenGLGDI.h"

OpenGLGDI::OpenGLGDI()
{
    GDI_DriverName = GDI_NAME_OPENGL;

    //IDs Attribuitions

    SetUName("Texture 1D",					GL_TEXTURE_1D);
    SetUName("Texture 2D",					GL_TEXTURE_2D);
    SetUName("Texture 3D",					GL_TEXTURE_3D);
    SetUName("Texture Cube Map",			GL_TEXTURE_CUBE_MAP);

    SetUName("Texture 1D Array",			GL_TEXTURE_1D_ARRAY);
    SetUName("Texture 2D Array",			GL_TEXTURE_2D_ARRAY);
    SetUName("Texture Cube Map Array",		GL_TEXTURE_CUBE_MAP_ARRAY);
    

    SetUName("Float",						GL_FLOAT);
    SetUName("Int",							GL_INT);
    SetUName("Double",						GL_DOUBLE);
    SetUName("Unsigned",					GL_UNSIGNED_INT);
    SetUName("Byte",						GL_BYTE);

    SetUName("Filter Linear",				GL_LINEAR);
    SetUName("Filter Nearest",				GL_NEAREST);

    SetUName("Format RED",					GL_R);
    SetUName("Format RG",					GL_RG);
    SetUName("Format RGB",					GL_RGB);
    SetUName("Format RGBA",					GL_RGBA);
    SetUName("Format Depth",				GL_DEPTH_COMPONENT);
    SetUName("Format Depth+Stencil",		GL_DEPTH_STENCIL);

    SetUName("Format Size RED 16",			GL_R16);
    SetUName("Format Size RED 16F",			GL_R16F);
    SetUName("Format Size RED 16I",			GL_R16I);
    SetUName("Format Size RED 16U",			GL_R16UI);
    SetUName("Format Size RED 32F",			GL_R32F);
    SetUName("Format Size RED 32I",			GL_R32I);
    SetUName("Format Size RED 32U",			GL_R32UI);
    
    SetUName("Format Size RG 16",			GL_RG16);
    SetUName("Format Size RG 16F",			GL_RG16F);
    SetUName("Format Size RG 16I",			GL_RG16I);
    SetUName("Format Size RG 16U",			GL_RG16UI);
    SetUName("Format Size RG 32F",			GL_RG32F);
    SetUName("Format Size RG 32I",			GL_RG32I);
    SetUName("Format Size RG 32U",			GL_RG32UI);

    SetUName("Format Size RGB 16",			GL_RGB16);
    SetUName("Format Size RGB 16F",			GL_RGB16F);
    SetUName("Format Size RGB 16I",			GL_RGB16I);
    SetUName("Format Size RGB 16U",			GL_RGB16UI);
    SetUName("Format Size RGB 32F",			GL_RGB32F);
    SetUName("Format Size RGB 32I",			GL_RGB32I);
    SetUName("Format Size RGB 32U",			GL_RGB32UI);

    SetUName("Format Size RGBA 16",			GL_RGBA16);
    SetUName("Format Size RGBA 16F",		GL_RGBA16F);
    SetUName("Format Size RGBA 16I",		GL_RGBA16I);
    SetUName("Format Size RGBA 16U",		GL_RGBA16UI);
    SetUName("Format Size RGBA 32F",		GL_RGBA32F);
    SetUName("Format Size RGBA 32I",		GL_RGBA32I);
    SetUName("Format Size RGBA 32U",		GL_RGBA32UI);

    SetUName("Target Diffuse",				GL_COLOR_ATTACHMENT0);
    SetUName("Target Normal",				GL_COLOR_ATTACHMENT1);
    SetUName("Target Specular",				GL_COLOR_ATTACHMENT2);
    SetUName("Target Depth",				GL_DEPTH_ATTACHMENT);
}

void OpenGLGDI::BeginGDI()
{
    //Gen Buffers

    gladLoadGLLoader((GLADloadproc) DISPLAY_PROCESS);
}

void OpenGLGDI::RenderGDI()
{
    //Render Scene
    glClearColor(0.F, 0.F, 1.F, 1.F);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenGLGDI::DestroyGDI()
{
    //Destroy Buffers
}
