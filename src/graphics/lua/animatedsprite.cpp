#include "animatedsprite.hpp"

int lua_cachesprite( lua_State* l ) {
    unsigned int argcount = lua_gettop( l );
    as::AnimatedSprite* sprite = new as::AnimatedSprite( luaL_checkstring( l, 1 ), luaL_checkstring( l, 2 ) ); // First argument is identifier
    // The rest of the arguments are animations
    for ( unsigned int i=3; i<1+argcount; i++ ) {
        as::Animation* animation = lua_checkanimation( l, i );
        sprite->addAnimation( animation );
    }
    // The resource manager will clean up anything we allocated for us.
    resourcemanager->addResource( (as::Resource*)new as::AnimatedSpriteResource( sprite->m_name, sprite ) );
    return 0;
}

int lua_registeranimatedsprite( lua_State* l ) {
    lua_getglobal( l, "Resource" );
    if ( lua_isnil( l, -1 ) ) {
        lua_newtable( l );
        lua_setglobal( l, "Resource" );
        lua_getglobal( l, "Resource" );
    }
    //lua_register( l, "cacheSprite", lua_cachesprite );
    lua_pushcfunction( l, lua_cachesprite );
    lua_setfield( l, -2, "cacheSprite" );
    lua_pop( l, 1 );
    return 0;
}
