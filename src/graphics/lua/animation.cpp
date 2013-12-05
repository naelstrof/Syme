#include "animation.hpp"

as::Animation* lua_toanimation( lua_State* l, int index ) {
    return (as::Animation*)luaL_checkudata( l, index, "Animation" );
}

as::Animation* lua_checkanimation( lua_State* l, int narg ) {
    as::Animation* foo = lua_toanimation( l, narg );
    if ( foo == NULL ) {
        luaL_argerror( l, narg, "attempt to index a NULL Animation!" );
    }
    return foo;
}

void lua_pushanimation( lua_State* l, as::Animation* animation ) {
    as::Animation* pointer = (as::Animation*)lua_newuserdata( l, sizeof(as::Animation) );
    memcpy( pointer, animation, sizeof( as::Animation ) );
    luaL_getmetatable( l, "Animation" );
    lua_setmetatable( l,-2 );
}

int lua_animation__newindex( lua_State* l ) {
    as::Animation* animation = lua_toanimation( l, 1 );
    if ( animation == NULL ) {
        return lua->error( l, "attempt to index a NULL Animation!" );
    }
    const char* field = luaL_checkstring(l,2);
    if ( !strcmp( field, "fps" ) ) {
        animation->m_fps = luaL_checknumber( l, 3 );
    } else if ( !strcmp( field, "name" ) ) {
        animation->m_name = luaL_checkstring( l, 3 );
    } else if ( !strcmp( field, "loop" ) ) {
        animation->m_loop = lua_toboolean( l, 3 );
    } else {
        return lua->error( l, "attempt to create new index on an Animation! (Animations can't hold random data! Use fps, name, or loop instead.)" );
    }

    return 0;
}

int lua_createanimation( lua_State* l ) {
    unsigned int argcount = lua_gettop( l );
    as::Animation* animation = new as::Animation();
    animation->m_name = luaL_checkstring( l, 1 ); // First argument is name
    animation->m_fps = luaL_checknumber( l, 2 ); // Second argument is fps
    animation->m_loop = lua_toboolean( l, 2 ); // Third argument is if it loops or not
    // The rest of the arguments are rectangles
    for ( unsigned int i=4; i<1+argcount; i++ ) {
        sf::IntRect* field = lua_checkintrect(l,i);
        animation->m_frames.push_back( *field );
    }
    lua_pushanimation( l, animation );
    return 1;
}

int lua_registeranimation( lua_State* l ) {
    // Create a new table called Animation
    luaL_newmetatable( l, "Animation" );
    // Register its new index function
    static const luaL_Reg animationLib[] {
        { "__newindex", lua_animation__newindex },
        { NULL, NULL }
    };
    luaL_register( l, NULL, animationLib );
    // Set its type to Animation
    lua_pushstring( l, "Animation" );
    lua_setfield( l, -2, "__type" );
    // Clear the stack
    lua_pop(l,1);

    // Create a function that puts a new as::Animation on the stack.
    lua_register( l, "Animation", lua_createanimation );
    return 0;
}
