#ifndef AS_LUA_VECTOR2_H_
#define AS_LUA_VECTOR2_H_

#include <SFML/Graphics/Rect.hpp>
#include <cstring> // for memcpy

#include "../lua.hpp"

sf::Vector2f*    lua_tovector( lua_State* l, int index );
sf::Vector2f*    lua_checkvector( lua_State* l, int narg );
void             lua_pushvector( lua_State* l, sf::Vector2f& vector );
int              lua_Vector2__newindex( lua_State* l );
int              lua_Vector2__index( lua_State* l );
int              lua_createvector( lua_State* l );
int              lua_registervector( lua_State* l );


#endif // AS_LUA_VECTOR2_H_
