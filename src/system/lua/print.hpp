#ifndef AS_SYSTEM_LUA_PRINT_H_
#define AS_SYSTEM_LUA_PRINT_H_

#define LUA_COMPAT_MODULE
#include <lua.hpp>

#include "../print.hpp"

int             lua_print( lua_State* l );
int             lua_registerprint( lua_State* l );

#endif // AS_SYSTEM_LUA_PRINT_H_
