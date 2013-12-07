#include "window.hpp"

as::Window* lua_towindow( lua_State* l, int index ) {
    return *( (as::Window**)luaL_checkudata( l, index, "Window" ) );
}

as::Window* lua_checkwindow( lua_State* l, int narg ) {
    as::Window* foo = lua_towindow( l, narg );
    if ( foo == NULL ) {
        luaL_argerror( l, narg, "attempt to index a NULL Window!" );
    }
    return foo;
}

void lua_pushwindow( lua_State* l, as::Window* window ) {
    as::Window** pointer = (as::Window**)lua_newuserdata( l, sizeof(as::Window*) );
    *pointer = window;
    luaL_getmetatable( l, "Window" );
    lua_setmetatable( l, -2 );
}

int lua_window__newindex( lua_State* l ) {
    as::Window* window = lua_towindow( l, 1 );
    if ( window == NULL ) {
        return lua->error( l, "attempt to index a NULL Window!" );
    }
    const char* field = luaL_checkstring(l,2);
    if ( !strcmp( field, "width" ) ) {
        sf::Vector2u size = window->m_window->getSize();
        window->m_window->setSize( sf::Vector2u( luaL_checknumber( l, 3 ), size.y ) );
    } else if ( !strcmp( field, "height" ) ) {
        sf::Vector2u size = window->m_window->getSize();
        window->m_window->setSize( sf::Vector2u( size.x, luaL_checknumber( l, 3 ) ) );
    } else if ( !strcmp( field, "x" ) ) {
        sf::Vector2i pos = window->m_window->getPosition();
        window->m_window->setPosition( sf::Vector2i( pos.x, luaL_checknumber( l, 3 ) ) );
    } else if ( !strcmp( field, "y" ) ) {
        sf::Vector2i pos = window->m_window->getPosition();
        window->m_window->setPosition( sf::Vector2i( luaL_checknumber( l, 3 ), pos.y ) );
    } else if ( !strcmp( field, "title" ) ) {
        window->m_window->setTitle( luaL_checkstring( l, 3 ) )
        window->m_name = luaL_checkstring( l, 3);
    } else if ( !strcmp( field, "vsync" ) ) {
        window->m_window->setVerticalSyncEnabled( lua_toboolean( l, 3 ) );
        window->m_vsync = lua_toboolean( l, 3 );
    } else if ( !strcmp( field, "framerateLimit" ) ) {
        window->m_window->setFramerateLimit( luaL_checknumber( l, 3 ) );
        window->m_maxfps = luaL_checknumber( l, 3 );
    } else {
        return lua->error( l, "attempt to create new index on an Window! (Windows can't hold random data!)" );
    }

    return 0;
}

int lua_window__index( lua_State* l ) {
    sf::Window* window = lua_towindow( l, 1 );
    if ( window == NULL ) {
        return lua->error( l, "attempt to index a NULL Window!" );
    }
    std::string field = luaL_checkstring(l,2);
    if ( field == "width" ) {
        lua_pushnumber( l, window->m_window->getSize().x );
        return 1;
    } else if ( field == "height" ) {
        lua_pushnumber( l, window->m_window->getSize().y );
        return 1;
    } else if ( field == "x" ) {
        lua_pushnumber( l, window->m_window->getPosition().x );
        return 1;
    } else if ( field == "y" ) {
        lua_pushnumber( l, window->m_window->getPosition().y );
        return 1;
    } else if ( field == "title" ) {
        lua_pushstring( l, window->m_name );
        return 1;
    } else if ( field == "vsync" ) {
        lua_pushstring( l, window->m_vsync );
        return 1;
    } else if ( field == "framerateLimit" ) {
        lua_pushstring( l, window->m_maxfps );
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

int lua_registerwindow( lua_State* l ) {
    // Create a new table called Window
    luaL_newmetatable( l, "Window" );
    // Register its new index function
    static const luaL_Reg windowLib[] {
        { "__newindex", lua_window__newindex },
        { "__index", lua_window__index },
        { NULL, NULL }
    };
    luaL_register( l, NULL, windowLib );
    // Set its type to Window
    lua_pushstring( l, "Window" );
    lua_setfield( l, -2, "__type" );
    // Clear the stack
    lua_pop(l,1);
    return 0;
}
