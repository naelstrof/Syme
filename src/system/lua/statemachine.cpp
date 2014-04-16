#include "statemachine.hpp"

int lua_setState( lua_State* l ) {
    std::string statename = lua_tostring( l, -1 );
    statemachine->setState( statename );
    as::printf( "Switching to state %\n", statename );
    return 0;
}

int lua_registerstatemachine( lua_State* l ) {
    lua_register( l, "setState", lua_setState );
    return 0;
}
