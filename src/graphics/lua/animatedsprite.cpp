#include "animatedsprite.hpp"

int lua_cachesprite( lua_State* l ) {
    unsigned int argcount = lua_gettop( l );
    as::AnimatedSprite* sprite = new as::AnimatedSprite( luaL_checkstring( l, 1 ), luaL_checkstring( l, 2 ) ); // First argument is identifier
    resourcemanager->addFileResource( (as::Resource*)new as::TextureResource( luaL_checkstring( l, 2 ) ) ); // Second argument is image path
    // The rest of the arguments are animations
    for ( unsigned int i=3; i<1+argcount; i++ ) {
        as::Animation* animation = lua_checkanimation( l, i );
        sprite->addAnimation( animation );
    }
    // The resource manager will clean up anything we allocated for us.
    resourcemanager->addProcessedResource( (as::Resource*)new as::AnimatedSpriteResource( sprite->m_name, sprite ) );
    return 0;
}

int lua_registeranimatedsprite( lua_State* l ) {
    lua_register( l, "CacheSprite", lua_cachesprite );
    return 0;
}
