#ifndef AS_LUA_INTRECT_H_
#define AS_LUA_INTRECT_H_

#include <SFML/Graphics/Rect.hpp>
#include <cstring> // for memcpy

#include "../lua.hpp"

sf::IntRect*    lua_tointrect( lua_State* l, int index );
sf::IntRect*    lua_checkintrect( lua_State* l, int narg );
void            lua_pushintrect( lua_State* l, sf::IntRect intrect );
int             lua_intrect__newindex( lua_State* l );
int             lua_intrect__index( lua_State* l );
int             lua_createintrect( lua_State* l );
int             lua_registerintrect( lua_State* l );


#endif // AS_LUA_INTRECT_H_
