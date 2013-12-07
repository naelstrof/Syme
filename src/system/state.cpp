#include "state.hpp"

as::State::State( std::string name, int luaReference ) :
    m_name( name ),
    m_luaReference( luaReference ) {
}

void as::State::tick( sf::Time deltaTime ) {
    if ( m_luaReference == LUA_NOREF ) {
        return;
    }

    // Get the function from our reference.
    lua_rawgeti( lua->m_l, LUA_REGISTRYINDEX, m_luaReference );
    lua_getfield( lua->m_l, -1, "onTick" );
    // Make sure the function exists.
    if ( !lua_isfunction( lua->m_l, -1 ) ) {
        lua_pop( lua->m_l, 2 );
        return;
    }
    // Push self to the function so we can refer to ourself.
    lua_rawgeti( lua->m_l, LUA_REGISTRYINDEX, m_luaReference );
    // First argument is dt as a number.
    lua_pushnumber( lua->m_l, deltaTime.asSeconds() );
    // Call the function.
    lua->call( lua->m_l, 2, 0 );
    lua_pop( lua->m_l, 1 );
}

void as::State::init() {
    if ( m_luaReference == LUA_NOREF ) {
        return;
    }

    lua_rawgeti( lua->m_l, LUA_REGISTRYINDEX, m_luaReference );
    lua_getfield( lua->m_l, -1, "onInit" );
    if ( !lua_isfunction( lua->m_l, -1 ) ) {
        lua_pop( lua->m_l, 2 );
        return;
    }
    lua_rawgeti( lua->m_l, LUA_REGISTRYINDEX, m_luaReference );
    lua->call( lua->m_l, 1, 0 );
    lua_pop( lua->m_l, 1 );
}

void as::State::exit() {
    if ( m_luaReference == LUA_NOREF ) {
        return;
    }

    lua_rawgeti( lua->m_l, LUA_REGISTRYINDEX, m_luaReference );
    lua_getfield( lua->m_l, -1, "onExit" );
    if ( !lua_isfunction( lua->m_l, -1 ) ) {
        lua_pop( lua->m_l, 2 );
        return;
    }
    lua_rawgeti( lua->m_l, LUA_REGISTRYINDEX, m_luaReference );
    lua->call( lua->m_l, 1, 0 );
    lua_pop( lua->m_l, 1 );
}

