#ifndef AS_SYSTEM_LUA_WINDOW_H_
#define AS_SYSTEM_LUA_WINDOW_H_

#include <string>

#include "../lua.hpp"
#include "../window.hpp"

as::Window*     lua_checkwindow( lua_State* l, int narg );
void            lua_pushwindow( lua_State* l, as::Window* animation );
int             lua_window__index( lua_State* l );
int             lua_window__newindex( lua_State* l );
int             lua_createwindow( lua_State* l );
int             lua_registerwindow( lua_State* l );

#endif // AS_SYSTEM_LUA_WINDOW_H_
