#include "intrect.hpp"

sf::IntRect* lua_tointrect( lua_State* l, int index ) {
    return (sf::IntRect*)luaL_checkudata( l, index, "IntRect" );
}

sf::IntRect* lua_checkintrect( lua_State* l, int narg ) {
    sf::IntRect* foo = lua_tointrect( l, narg );
    if ( foo == NULL ) {
        luaL_argerror( l, narg, "attempt to index a NULL IntRect!" );
    }
    return foo;
}

void lua_pushintrect( lua_State* l, sf::IntRect* intrect ) {
    sf::IntRect* pointer = (sf::IntRect*)lua_newuserdata( l, sizeof(sf::IntRect) );
    memcpy( pointer, intrect, sizeof( sf::IntRect ) );
    luaL_getmetatable( l, "IntRect" );
    lua_setmetatable( l,-2 );
}

int lua_intrect__newindex( lua_State* l ) {
    sf::IntRect* intrect = lua_tointrect( l, 1 );
    if ( intrect == NULL ) {
        return lua->error( l, "attempt to index a NULL IntRect!" );
    }
    const char* field = luaL_checkstring(l,2);
    if ( !strcmp( field, "left" ) ) {
        intrect->left = luaL_checknumber( l, 3 );
    } else if ( !strcmp( field, "top" ) ) {
        intrect->top = luaL_checknumber( l, 3 );
    } else if ( !strcmp( field, "width" ) ) {
        intrect->width = luaL_checknumber( l, 3 );
    } else if ( !strcmp( field, "height" ) ) {
        intrect->height = luaL_checknumber( l, 3 );
    } else {
        return lua->error( l, "attempt to create new index on an IntRect! (IntRects can't hold random data! Use left, top, width, or height instead.)" );
    }

    return 0;
}

int luaIntRect__index( lua_State* l ) {
    sf::IntRect* intrect = lua_tointrect( l, 1 );
    if ( intrect == NULL ) {
        return lua->error( l, "attempt to index a NULL IntRect!" );
    }
    std::string field = luaL_checkstring(l,2);
    if ( field == "left" ) {
        lua_pushnumber( l, intrect->left );
        return 1;
    } else if ( field == "top" ) {
        lua_pushnumber( l, intrect->top );
        return 1;
    } else if ( field == "width" ) {
        lua_pushnumber( l, intrect->width );
        return 1;
    } else if ( field == "height" ) {
        lua_pushnumber( l, intrect->height );
        return 1;
    }
    lua_getmetatable( l, 1 );
    lua_pushvalue( l, 2 );
    lua_gettable( l, -2 );
    if ( lua_isnil( l, -1 ) ) {
        return 0;
    }
    return 1;
}

int lua_createintrect( lua_State* l ) {
    sf::IntRect* intrect = new sf::IntRect();
    intrect->left = luaL_checknumber( l, 1 );
    intrect->top = luaL_checknumber( l, 2 );
    intrect->width = luaL_checknumber( l, 3 );
    intrect->height = luaL_checknumber( l, 4 );
    lua_pushintrect( l, intrect );
    return 1;
}

int lua_registerintrect( lua_State* l ) {
    // Create a new table called IntRect
    luaL_newmetatable( l, "IntRect" );
    // Register its new index function
    static const luaL_Reg intrectLib[] {
        { "__newindex", lua_intrect__newindex },
        { "__index", lua_intrect__index },
        { NULL, NULL }
    };
    luaL_register( l, NULL, intrectLib );
    // Set its type to IntRect
    lua_pushstring( l, "IntRect" );
    lua_setfield( l, -2, "__type" );
    // Clear the stack
    lua_pop(l,1);

    // Create a function that puts a new sf::IntRect on the stack.
    lua_register( l, "IntRect", lua_createintrect );
    return 0;
}
