#ifndef AS_LUA_ANIMATEDSPRITE_H_
#define AS_LUA_ANIMATEDSPRITE_H_

#define LUA_COMPAT_MODULE
#include <lua.hpp>

#include "animation.hpp"
#include "../scene.hpp"
#include "../animation.hpp"
#include "../animatedsprite.hpp"
#include "../resource/animatedsprite.hpp"
#include "../../system/lua/vector.hpp"

int                     lua_cachesprite( lua_State* l );

as::AnimatedSprite*     lua_toanimatedsprite( lua_State* l, int index );
as::AnimatedSprite*     lua_checkanimatedsprite( lua_State* l, int narg );
void                    lua_pushanimatedsprite( lua_State* l, as::AnimatedSprite* animatedsprite );
int                     lua_animatedsprite__newindex( lua_State* l );
int                     lua_animatedsprite__index( lua_State* l );
int                     lua_animatedsprite__gc( lua_State* l );
int                     lua_animatedsprite_setPos( lua_State* l );
int                     lua_animatedsprite_getPos( lua_State* l );
int                     lua_animatedsprite_move( lua_State* l );
int                     lua_createanimatedsprite( lua_State* l );
int                     lua_registeranimatedsprite( lua_State* l );
int                     lua_registeranimatedsprite( lua_State* l );

#endif // AS_LUA_ANIMATION_H_
