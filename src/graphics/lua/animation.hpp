#ifndef AS_LUA_ANIMATION_H_
#define AS_LUA_ANIMATION_H_

#include <string>

#include "../../system/lua.hpp"
#include "../../system/lua/intrect.hpp"
#include "../animation.hpp"
#include "../animatedsprite.hpp"

as::Animation*  lua_toanimation( lua_State* l, int index );
as::Animation*  lua_checkanimation( lua_State* l, int narg );
void            lua_pushanimation( lua_State* l, as::Animation* animation );
int             lua_animation__newindex( lua_State* l );
int             lua_animation__gc( lua_State* l );
int             lua_createanimation( lua_State* l );
int             lua_registeranimation( lua_State* l );

#endif // AS_LUA_ANIMATION_H_
