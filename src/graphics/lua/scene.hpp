#ifndef AS_LUA_SCENE_H_
#define AS_LUA_SCENE_H_

#define LUA_COMPAT_MODULE
#include <lua.hpp>

#include "../scene.hpp"
#include "../../system/lua/time.hpp"

int                     lua_registerscene( lua_State* l );

#endif // AS_LUA_SCENE_H_
