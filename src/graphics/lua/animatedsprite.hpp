#ifndef AS_LUA_ANIMATEDSPRITE_H_
#define AS_LUA_ANIMATEDSPRITE_H_

#define LUA_COMPAT_MODULE
#include <lua.hpp>

#include "animation.hpp"
#include "../animation.hpp"
#include "../animatedsprite.hpp"
#include "../resource/animatedsprite.hpp"

int lua_cachesprite( lua_State* l );
int lua_registeranimatedsprite( lua_State* l );

#endif // AS_LUA_ANIMATION_H_
