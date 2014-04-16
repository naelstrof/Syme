#include "animatedsprite.hpp"

as::AnimatedSprite* lua_toanimatedsprite( lua_State* l, int index ) {
    return *( (as::AnimatedSprite**)luaL_checkudata( l, index, "AnimatedSprite" ) );
}

as::AnimatedSprite* lua_checkanimatedsprite( lua_State* l, int narg ) {
    as::AnimatedSprite* foo = lua_toanimatedsprite( l, narg );
    if ( foo == NULL ) {
        luaL_argerror( l, narg, "attempt to index a NULL AnimatedSprite!" );
    }
    return foo;
}

void lua_pushanimatedsprite( lua_State* l, as::AnimatedSprite* animatedsprite ) {
    // We only need lua to keep track of the actual pointer, since we handle the pointer inside of scene.
    as::AnimatedSprite** pointer = (as::AnimatedSprite**)lua_newuserdata( l, sizeof(as::AnimatedSprite*) );
    *pointer = animatedsprite;
    luaL_getmetatable( l, "AnimatedSprite" );
    lua_setmetatable( l,-2 );
}

int lua_animatedsprite__newindex( lua_State* l ) {
    as::AnimatedSprite* animatedsprite = lua_toanimatedsprite( l, 1 );
    if ( animatedsprite == NULL ) {
        return lua->error( l, "attempt to index a NULL AnimatedSprite!" );
    }
    //const char* field = luaL_checkstring(l,2);
    /*if ( !strcmp( field, "left" ) ) {
        animatedsprite->left = luaL_checknumber( l, 3 );
    } else if ( !strcmp( field, "top" ) ) {
        animatedsprite->top = luaL_checknumber( l, 3 );
    } else if ( !strcmp( field, "width" ) ) {
        animatedsprite->width = luaL_checknumber( l, 3 );
    } else if ( !strcmp( field, "height" ) ) {
        animatedsprite->height = luaL_checknumber( l, 3 );
    } else {*/
        return lua->error( l, "attempt to create new index on an AnimatedSprite! (AnimatedSprites can't hold random data!)" );
    //}

    return 0;
}

int lua_animatedsprite__gc( lua_State* l ) {
    as::AnimatedSprite* animatedsprite = lua_toanimatedsprite( l, 1 );
    if ( animatedsprite == NULL ) {
        return lua->error( l, "attempt to index a NULL AnimatedSprite!" );
    }
    scene->remove( animatedsprite );
    delete animatedsprite;
    return 0;
}

int lua_animatedsprite_remove( lua_State* l ) {
    as::AnimatedSprite* animatedsprite = lua_toanimatedsprite( l, 1 );
    if ( animatedsprite == NULL ) {
        return lua->error( l, "attempt to index a NULL AnimatedSprite!" );
    }
    scene->remove( animatedsprite );
    return 0;
}

int lua_animatedsprite__index( lua_State* l ) {
    as::AnimatedSprite* animatedsprite = lua_toanimatedsprite( l, 1 );
    if ( animatedsprite == NULL ) {
        return lua->error( l, "attempt to index a NULL AnimatedSprite!" );
    }
    /*std::string field = luaL_checkstring(l,2);
    if ( field == "left" ) {
        lua_pushnumber( l, animatedsprite->left );
        return 1;
    } else if ( field == "top" ) {
        lua_pushnumber( l, animatedsprite->top );
        return 1;
    } else if ( field == "width" ) {
        lua_pushnumber( l, animatedsprite->width );
        return 1;
    } else if ( field == "height" ) {
        lua_pushnumber( l, animatedsprite->height );
        return 1;
    }*/
    lua_getmetatable( l, 1 );
    lua_pushvalue( l, 2 );
    lua_gettable( l, -2 );
    if ( lua_isnil( l, -1 ) ) {
        return 0;
    }
    return 1;
}

int lua_animatedsprite_getPos( lua_State* l ) {
    as::AnimatedSprite* animatedsprite = lua_toanimatedsprite( l, 1 );
    if ( animatedsprite == NULL ) {
        return lua->error( l, "attempt to index a NULL AnimatedSprite!" );
    }
    lua_pushvector( l, (sf::Vector2f&)animatedsprite->getPosition() );
    return 1;
}

int lua_animatedsprite_setPos( lua_State* l ) {
    as::AnimatedSprite* animatedsprite = lua_toanimatedsprite( l, 1 );
    if ( animatedsprite == NULL ) {
        return lua->error( l, "attempt to index a NULL AnimatedSprite!" );
    }
    animatedsprite->setPosition( *lua_checkvector( l, 2 ) );
    return 0;
}

int lua_animatedsprite_move( lua_State* l ) {
    as::AnimatedSprite* animatedsprite = lua_toanimatedsprite( l, 1 );
    if ( animatedsprite == NULL ) {
        return lua->error( l, "attempt to index a NULL AnimatedSprite!" );
    }
    animatedsprite->move( *lua_checkvector( l, 2 ) );
    return 0;
}

int lua_createanimatedsprite( lua_State* l ) {
    // ResourceManager will copy an animated sprite for us.
    as::AnimatedSprite* animatedsprite = (as::AnimatedSprite*)resourcemanager->getResource( luaL_checkstring( l, 1 ) );
    // Add it to the scene and make sure that the scene ticks it for us.
    scene->add( animatedsprite );
    lua_pushanimatedsprite( l, animatedsprite );
    return 1;
}

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
    // Create a new table called AnimatedSprite
    luaL_newmetatable( l, "AnimatedSprite" );
    // Register its new index function
    static const luaL_Reg animatedspriteLib[] {
        { "__newindex", lua_animatedsprite__newindex },
        { "__index", lua_animatedsprite__index },
        { "__gc", lua_animatedsprite__gc },
        { "remove", lua_animatedsprite_remove },
        { "getPos", lua_animatedsprite_getPos },
        { "setPos", lua_animatedsprite_setPos },
        { "move", lua_animatedsprite_move },
        { NULL, NULL }
    };
    luaL_register( l, NULL, animatedspriteLib );
    // Set its type to AnimatedSprite
    lua_pushstring( l, "AnimatedSprite" );
    lua_setfield( l, -2, "__type" );
    // Clear the stack
    lua_pop(l,1);

    // Create a function that puts a new as::AnimatedSprite on the stack.
    lua_register( l, "AnimatedSprite", lua_createanimatedsprite );

    // Now we create the cachesprite function
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
