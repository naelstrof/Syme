#include "state.hpp"

as::State::State( std::string name, int luaReference ) :
    m_name( name ),
    m_luaReference( luaReference ) {
}

void as::State::tick( sf::Time deltaTime, lua_State* l ) {
    if ( m_luaReference == LUA_NOREF ) {
        return;
    }

    // Get the function from our reference.
    lua_rawgeti( l, LUA_REGISTRYINDEX, m_luaReference );
    lua_getfield( l, -1, "onTick" );
    // Make sure the function exists.
    if ( !lua_isfunction( l, -1 ) ) {
        lua_pop( l, 2 );
        return;
    }
    // Push self to the function so we can refer to ourself.
    lua_rawgeti( l, LUA_REGISTRYINDEX, m_luaReference );
    // First argument is dt as a number.
    lua_pushnumber( l, deltaTime.asSeconds() );
    // Call the function.
    lua->call( l, 2, 0 );
    lua_pop( l, 1 );
}

void as::State::init( lua_State* l ) {
    if ( m_luaReference == LUA_NOREF ) {
        return;
    }

    lua_rawgeti( l, LUA_REGISTRYINDEX, m_luaReference );
    lua_getfield( l, -1, "onInit" );
    if ( !lua_isfunction( l, -1 ) ) {
        lua_pop( l, 2 );
        return;
    }
    lua_rawgeti( l, LUA_REGISTRYINDEX, m_luaReference );
    lua->call( l, 1, 0 );
    lua_pop( l, 1 );
}

void as::State::exit( lua_State* l ) {
    if ( m_luaReference == LUA_NOREF ) {
        return;
    }

    lua_rawgeti( l, LUA_REGISTRYINDEX, m_luaReference );
    lua_getfield( l, -1, "onExit" );
    if ( !lua_isfunction( l, -1 ) ) {
        lua_pop( l, 2 );
        return;
    }
    lua_rawgeti( l, LUA_REGISTRYINDEX, m_luaReference );
    lua->call( l, 1, 0 );
    lua_pop( l, 1 );
}

