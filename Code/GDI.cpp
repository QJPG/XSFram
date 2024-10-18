#include "GDI.h"

GDI::GDI()
{
    GDI_DriverName = GDI_NAME_UNKNWN;
}

const char* GDI::GetDriverName() const
{
    return GDI_DriverName;
}

void GDI::SetUName(str name, u32 val)
{
    GDIUNAMES[name] = val;
}

u32 GDI::GetUName(str name, u32 dft) const
{
    auto i = GDIUNAMES.find(name);

    if (i != GDIUNAMES.end()) return i->second;

    return dft;
}
