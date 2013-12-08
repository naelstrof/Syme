#ifndef AS_LUA_TIME_H_
#define AS_LUA_TIME_H_

#include <SFML/System/Time.hpp>
#include <cstring> // for memcpy

#include "../lua.hpp"

sf::Time*       lua_totime( lua_State* l, int index );
sf::Time*       lua_checktime( lua_State* l, int narg );
void            lua_pushtime( lua_State* l, sf::Time time );
int             lua_time__newindex( lua_State* l );
int             lua_time__index( lua_State* l );
//int             lua_createtime( lua_State* l );
int             lua_time_asSeconds( lua_State* l );
int             lua_registertime( lua_State* l );


#endif // AS_LUA_TIME_H_
