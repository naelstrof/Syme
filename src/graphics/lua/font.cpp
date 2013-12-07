#include "font.hpp"

int lua_cachefont( lua_State* l ) {
    // First argument is name, second is file path
    as::FontResource* resource = new as::FontResource( luaL_checkstring( l, 1 ), luaL_checkstring( l, 2 ) );
    // The resource manager will clean up anything we allocated for us.
    resourcemanager->addResource( (as::Resource*)resource );
    return 0;
}

int lua_registerfont( lua_State* l ) {
    lua_getglobal( l, "Resource" );
    if ( lua_isnil( l, -1 ) ) {
        lua_newtable( l );
        lua_setglobal( l, "Resource" );
        lua_getglobal( l, "Resource" );
    }
    //lua_register( l, "cacheSprite", lua_cachesprite );
    lua_pushcfunction( l, lua_cachefont );
    lua_setfield( l, -2, "cacheFont" );
    lua_pop( l, 1 );
    return 0;
}
