#include "scene.hpp"

int lua_scene_tick( lua_State* l ) {
    sf::Time* dt = lua_checktime( l, 1 );
    scene->tick( *dt );
    return 0;
}

int lua_registerscene( lua_State* l ) {
    // Now we create the cachesprite function
    lua_getglobal( l, "Scene" );
    if ( lua_isnil( l, -1 ) ) {
        lua_newtable( l );
        lua_setglobal( l, "Scene" );
        lua_getglobal( l, "Scene" );
    }
    //lua_register( l, "cacheSprite", lua_cachesprite );
    lua_pushcfunction( l, lua_scene_tick );
    lua_setfield( l, -2, "tick" );
    lua_pop( l, 1 );
    return 0;
}
