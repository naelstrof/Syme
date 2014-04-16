#ifndef AS_SYSTEM_LUA_STATEMACHINE_H_
#define AS_SYSTEM_LUA_STATEMACHINE_H_

#include "../statemachine.hpp"

int             lua_setState( lua_State* l );
int             lua_registerstatemachine( lua_State* l );

#endif // AS_SYSTEM_LUA_STATEMACHINE_H_
