#include "font.hpp"

int lua_cachefont( lua_State* l ) {
    // First argument is name, second is file path
    as::FontResource* resource = new as::FontResource( luaL_checkstring( l, 1 ), luaL_checkstring( l, 2 ) );
    // The resource manager will clean up anything we allocated for us.
    resourcemanager->addResource( (as::Resource*)resource );
    return 0;
}

int lua_registerfont( lua_State* l ) {
    lua_register( l, "CacheFont", lua_cachefont );
    return 0;
}
