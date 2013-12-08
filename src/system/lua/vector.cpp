#include "vector.hpp"

sf::Vector2f* lua_tovector( lua_State* l, int index ) {
    return (sf::Vector2f*)luaL_checkudata( l, index, "Vector" );
}

sf::Vector2f* lua_checkvector( lua_State* l, int narg ) {
    sf::Vector2f* foo = lua_tovector( l, narg );
    if ( foo == NULL ) {
        luaL_argerror( l, narg, "attempt to index a NULL Vector!" );
    }
    return foo;
}

void lua_pushvector( lua_State* l, sf::Vector2f* vector ) {
    sf::Vector2f* pointer = (sf::Vector2f*)lua_newuserdata( l, sizeof(sf::Vector2f) );
    memcpy( pointer, vector, sizeof( sf::Vector2f ) );
    luaL_getmetatable( l, "Vector" );
    lua_setmetatable( l,-2 );
}

int lua_vector__newindex( lua_State* l ) {
    sf::Vector2f* Vector = lua_tovector( l, 1 );
    if ( Vector == NULL ) {
        return lua->error( l, "attempt to index a NULL Vector!" );
    }
    const char* field = luaL_checkstring(l,2);
    if ( !strcmp( field, "x" ) ) {
        Vector->x = luaL_checknumber( l, 3 );
    } else if ( !strcmp( field, "y" ) ) {
        Vector->y = luaL_checknumber( l, 3 );
    } else {
        return lua->error( l, "attempt to create new index on an Vector! (Vectors can't hold random data! Use x or y instead.)" );
    }

    return 0;
}

int lua_vector__index( lua_State* l ) {
    sf::Vector2f* Vector = lua_tovector( l, 1 );
    if ( Vector == NULL ) {
        return lua->error( l, "attempt to index a NULL Vector!" );
    }
    std::string field = luaL_checkstring(l,2);
    if ( field == "x" ) {
        lua_pushnumber( l, Vector->x );
        return 1;
    } else if ( field == "y" ) {
        lua_pushnumber( l, Vector->y );
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

int lua_createvector( lua_State* l ) {
    sf::Vector2f* Vector = new sf::Vector2f();
    Vector->x = luaL_checknumber( l, 1 );
    Vector->y = luaL_checknumber( l, 2 );
    lua_pushvector( l, Vector );
    return 1;
}

int lua_registervector( lua_State* l ) {
    // Create a new table called Vector
    luaL_newmetatable( l, "Vector" );
    // Register its new index function
    static const luaL_Reg VectorLib[] {
        { "__newindex", lua_vector__newindex },
        { "__index", lua_vector__index },
        { NULL, NULL }
    };
    luaL_register( l, NULL, VectorLib );
    // Set its type to Vector
    lua_pushstring( l, "Vector" );
    lua_setfield( l, -2, "__type" );
    // Clear the stack
    lua_pop(l,1);

    // Create a function that puts a new sf::Vector2f on the stack.
    lua_register( l, "Vector", lua_createvector );
    return 0;
}
