#ifndef AS_LUA_FONT_H_
#define AS_LUA_FONT_H_

#define LUA_COMPAT_MODULE
#include <lua.hpp>

#include "animation.hpp"
#include "../resource/font.hpp"

int lua_cachefont( lua_State* l );
int lua_registerfont( lua_State* l );

#endif // AS_LUA_FONT_H_
