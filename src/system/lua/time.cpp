#include "time.hpp"

sf::Time* lua_totime( lua_State* l, int index ) {
    return (sf::Time*)luaL_checkudata( l, index, "Time" );
}

sf::Time* lua_checktime( lua_State* l, int narg ) {
    sf::Time* foo = lua_totime( l, narg );
    if ( foo == NULL ) {
        luaL_argerror( l, narg, "attempt to index a NULL Time!" );
    }
    return foo;
}

void lua_pushtime( lua_State* l, sf::Time time ) {
    sf::Time* pointer = (sf::Time*)lua_newuserdata( l, sizeof(sf::Time) );
    memcpy( pointer, &time, sizeof( sf::Time ) );
    luaL_getmetatable( l, "Time" );
    lua_setmetatable( l,-2 );
}

int lua_time__newindex( lua_State* l ) {
    sf::Time* time = lua_totime( l, 1 );
    if ( time == NULL ) {
        return lua->error( l, "attempt to index a NULL Time!" );
    }
    /*const char* field = luaL_checkstring(l,2);
    if ( !strcmp( field, "left" ) ) {
        time->left = luaL_checknumber( l, 3 );
    } else if ( !strcmp( field, "top" ) ) {
        time->top = luaL_checknumber( l, 3 );
    } else if ( !strcmp( field, "width" ) ) {
        time->width = luaL_checknumber( l, 3 );
    } else if ( !strcmp( field, "height" ) ) {
        time->height = luaL_checknumber( l, 3 );
    } else {*/
        return lua->error( l, "attempt to create new index on an Time! (Times can't hold random data!)" );
    //}

    return 0;
}

int lua_time_asSeconds( lua_State* l ) {
    sf::Time* time = lua_totime( l, 1 );
    lua_pushnumber( l, time->asSeconds() );
    return 1;
}

int lua_time__index( lua_State* l ) {
    sf::Time* time = lua_totime( l, 1 );
    if ( time == NULL ) {
        return lua->error( l, "attempt to index a NULL Time!" );
    }
    /*std::string field = luaL_checkstring(l,2);
    if ( field == "left" ) {
        lua_pushnumber( l, time->left );
        return 1;
    } else if ( field == "top" ) {
        lua_pushnumber( l, time->top );
        return 1;
    } else if ( field == "width" ) {
        lua_pushnumber( l, time->width );
        return 1;
    } else if ( field == "height" ) {
        lua_pushnumber( l, time->height );
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

/*int lua_createtime( lua_State* l ) {
    sf::Time* time = new sf::Time();
    time->left = luaL_checknumber( l, 1 );
    time->top = luaL_checknumber( l, 2 );
    time->width = luaL_checknumber( l, 3 );
    time->height = luaL_checknumber( l, 4 );
    lua_pushtime( l, time );
    return 1;
}*/

int lua_registertime( lua_State* l ) {
    // Create a new table called Time
    luaL_newmetatable( l, "Time" );
    // Register its new index function
    static const luaL_Reg timeLib[] {
        { "__newindex", lua_time__newindex },
        { "__index", lua_time__index },
        { "asSeconds", lua_time_asSeconds },
        { NULL, NULL }
    };
    luaL_register( l, NULL, timeLib );
    // Set its type to Time
    lua_pushstring( l, "Time" );
    lua_setfield( l, -2, "__type" );
    // Clear the stack
    lua_pop(l,1);

    // Create a function that puts a new sf::Time on the stack.
    // lua_register( l, "Time", lua_createtime );
    return 0;
}
