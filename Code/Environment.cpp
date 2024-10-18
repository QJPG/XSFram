#include "Environment.h"

std::map<Environment::CSTR, Environment::I32>  Environment::ENV_I32VARS;
std::map<Environment::CSTR, Environment::CSTR> Environment::ENV_CSTRVARS;

Environment::BL Environment::UPDATE_RELEASED = true;

void Environment::SET_I32_ENVVAR(CSTR VARNAME, I32 VALUE)
{
    ENV_I32VARS[VARNAME] = VALUE;
    UPDATE_RELEASED = false;
}

void Environment::SET_STR_ENVVAR(CSTR VARNAME, CSTR VALUE)
{
    ENV_CSTRVARS[VARNAME] = VALUE;
    UPDATE_RELEASED = false;
}

void Environment::GET_I32_ENVVAR(CSTR VARNAME, I32 & OUTVAR)
{
    auto interator = ENV_I32VARS.find(VARNAME);

    if (interator != ENV_I32VARS.end()) {
        OUTVAR = interator->second;
    }
}

void Environment::GET_STR_ENVVAR(CSTR VARNAME, CSTR & OUTVAR)
{
    auto interator = ENV_CSTRVARS.find(VARNAME);

    if (interator != ENV_CSTRVARS.end()) {
        OUTVAR = interator->second;
    }
}

bool Environment::HAS_ENV_VARS_UPDATES()
{
    if (UPDATE_RELEASED == false) {
        UPDATE_RELEASED = true;

        return true;
    }

    return false;
}
