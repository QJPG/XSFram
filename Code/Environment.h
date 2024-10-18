#pragma once

#include <map>
#include <string>

class Environment
{
    typedef const char* CSTR;
    typedef int			I32;
    typedef size_t		SZU;
    typedef char		U8;
    typedef bool		BL;

    static std::map<CSTR, I32>		ENV_I32VARS;
    static std::map<CSTR, CSTR>		ENV_CSTRVARS;

    static BL						UPDATE_RELEASED;

public:
    static void SET_I32_ENVVAR(CSTR VARNAME, I32 VALUE);
    static void SET_STR_ENVVAR(CSTR VARNAME, CSTR VALUE);

    static void	GET_I32_ENVVAR(CSTR VARNAME, I32 & OUTVAR);
    static void GET_STR_ENVVAR(CSTR VARNAME, CSTR & OUTVAR);

    static bool HAS_ENV_VARS_UPDATES();
};

