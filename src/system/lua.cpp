#include "lua.hpp"

as::Lua* lua = new as::Lua();

as::Lua::Lua() {
    m_l = luaL_newstate();

    lua_atpanic( m_l, luaOnPanic );

    luaL_openlibs( m_l );
}

as::Lua::~Lua() {
    lua_close( m_l );
}

int as::Lua::init() {
    lua_registerprint( m_l );
    lua_registertime( m_l );
    lua_registerintrect( m_l );
    lua_registervector( m_l );
    lua_registeranimation( m_l );

    lua_registeranimatedsprite( m_l );
    lua_registerfont( m_l );
    lua_registerscene( m_l );
    lua_registerstatemachine( m_l );

    return 0;
}

int as::Lua::doFile( std::string dir ) {
    as::FileRead file( dir );
    if ( !file.good() ) {
        as::printf( "ERR Couldn't parse % as a lua file!\n", dir );
        return 1;
    }

    char* filedata = new char[ file.size() + 1 ]; // +1 for a terminating null character.
    file.read( filedata, file.size() );
    filedata[ file.size() ] = '\0'; // Ensure the 'string' as terminated just in case we're parsing some randomass file.

    // Finally parse the string and check for errors.
    int err = luaL_asdostring( m_l, filedata, dir.c_str() );
    delete[] filedata;
    if ( err ) {
        std::string error = lua_tostring( m_l, -1 );
        // We got to change the error message to reflect that we're actually getting an error in a file, rather than a string.
        std::size_t place = error.find( "[string" );
        while ( place != std::string::npos ) {
            error.replace( place, 7, "[file" );
            place = error.find( "[string" );
        }
        as::printf( "ERR %\n", error );
        return 1;
    }
    return 0;
}

int as::Lua::doFolder( std::string dir ) {
    std::vector<std::string> files = filesystem->getFiles( dir );
    if ( files.size() <= 0 ) {
        as::printf( "WRN Couldn't find anything in %, does it exist?\n", dir );
        return 1;
    }
    int results = 0;
    for ( unsigned int i=0;i<files.size();i++ ) {
        if ( files[i].find(".lua") == files[i].size()-4 ) {
            results += doFile( files[i] );
        }
    }
    return results;
}

int as::Lua::call( lua_State* l, int nargs, int nresults ) {
    if ( lua_pcall( l, nargs, nresults, 0 ) ) {
        std::string error = lua_tostring( l, -1 );
        std::size_t place = error.find( "[string" );
        while ( place != std::string::npos ) {
            error.replace( place, 7, "[file" );
            place = error.find( "[string" );
        }
        as::printf( "ERR Lua: %\n", error );

        traceback( l );
        if ( error != lua_tostring( l, -1 ) ) {
            error = lua_tostring( l, -1 );
            place = error.find( "[string" );
            while ( place != std::string::npos ) {
                error.replace( place, 7, "[file" );
                place = error.find( "[string" );
            }
            as::printf( "ERR Lua: %\n", error );
        }
        return 1;
    }
    return 0;
}

int as::Lua::traceback( lua_State* l ) {
    if ( !lua_isstring( l, 1 ) ) {
        return 1;
    }
    lua_getglobal( l, "debug" );
    if ( !lua_istable( l, -1 ) ) {
        lua_pop( l, 1 );
        return 1;
    }
    lua_getfield( l, -1, "traceback" );
    if ( !lua_isfunction( l, -1 ) ) {
        lua_pop( l, 2 );
        return 1;
    }
    lua_pushvalue( l, 1 );
    lua_pushinteger( l, 2 );
    lua_call( l, 2, 1 );
    return 1;
}

void as::Lua::copy( lua_State* l, int index ) {
    lua_newtable( l );
    lua_pushnil( l );
    while ( lua_next( l, index ) != 0 ) {
        lua_pushvalue( l, -2 );
        lua_insert( l, -2 );
        lua_settable( l, -4 );
    }
}

void as::Lua::copyMeta( lua_State* l, int index, std::string newname ) {
    luaL_newmetatable( l, newname.c_str() );
    lua_pushnil( l );
    while ( lua_next( l, index ) != 0 ) {
        lua_pushvalue( l, -2 );
        lua_insert( l, -2 );
        lua_settable( l, -4 );
    }
}

int as::Lua::getBool( lua_State* l, std::string name, bool* ret ) {
    lua_getfield( l, -1, name.c_str() );
    if ( !lua_isboolean( l, -1 ) ) {
        lua_pop( l, 1 );
        return 1;
    }
    *ret = (bool)lua_toboolean( l, -1 );
    lua_pop( l, 1 );
    return 0;
}

int as::Lua::getString( lua_State* l, std::string name, std::string* ret ) {
    lua_getfield( l, -1, name.c_str() );
    if ( !lua_isstring( l, -1 ) ) {
        lua_pop( l, 1 );
        return 1;
    }
    *ret = lua_tostring( l, -1 );
    lua_pop( l, 1 );
    return 0;
}

int as::Lua::getNumber( lua_State* l, std::string name, float* ret ) {
    lua_getfield( l, -1, name.c_str() );
    if ( !lua_isnumber( l, -1 ) ) {
        lua_pop( l, 1 );
        return 1;
    }
    *ret = lua_tonumber( l, -1 );
    lua_pop( l, 1 );
    return 0;
}

int as::luaOnPanic( lua_State* l ) {
    std::string error = lua_tostring( l, -1 );
    as::printf( "ERR %\n", error );
    lua->traceback( l );
    if ( error != lua_tostring( l, -1 ) ) {
        error = lua_tostring( l, -1 );
        as::printf( "ERR %\n", error );
    }
    return 0;
}

int as::luaL_loadstring( lua_State* l, const char* s, const char* dir ) {
    return luaL_loadbuffer( l, s, strlen(s), dir );
}

int as::Lua::error( lua_State* l, std::string message ) {
    lua_Debug ar1;
    lua_getstack( l, 1, &ar1 );
    lua_getinfo( l, "fl", &ar1 );
    lua_Debug ar2;
    lua_getinfo( l, ">S", &ar2 );
    lua_pushfstring( l, "%s:%d: %s", ar2.short_src, ar1.currentline, message.c_str() );
    return lua_error( l );
}
