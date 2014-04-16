#ifndef AS_LUA_H_
#define AS_LUA_H_

// Required to use luaL_register, not sure of any alternatives.
#define LUA_COMPAT_MODULE
#include <lua.hpp>
// For strlen()
#include <cstring>

#include "filesystem.hpp"
#include "print.hpp"

#include "../graphics/lua/animation.hpp"
#include "../graphics/lua/animatedsprite.hpp"
#include "../graphics/lua/font.hpp"
#include "../graphics/lua/scene.hpp"

#include "lua/print.hpp"
#include "lua/intrect.hpp"
#include "lua/time.hpp"
#include "lua/vector.hpp"
#include "lua/statemachine.hpp"

// Here we define our own lua dostring function that properly registers file location for error messages.
#define luaL_asdostring( l, s, n ) \
        (as::luaL_loadstring( l, s, n ) || lua_pcall( l, 0, LUA_MULTRET, 0 ))

namespace as {

class Lua {
public:
                Lua();
                ~Lua();
    lua_State*  m_l;
    std::string m_configFolder;
    int         init();
    int         call( lua_State* l, int nargs, int nresults );
    int         traceback( lua_State* l );
    int         doFile( std::string dir );
    int         doFolder( std::string dir );
    void        copy( lua_State* l, int index );
    void        copyMeta( lua_State* l, int index, std::string newname );
    int         getBool( lua_State* l, std::string name, bool* ret );
    int         getString( lua_State* l, std::string name, std::string* ret );
    int         getNumber( lua_State* l, std::string name, float* ret );
    int         error( lua_State* l, std::string message );
};

int luaL_loadstring( lua_State* l, const char* s, const char* dir );
int luaOnPanic( lua_State* l );

};

extern as::Lua* lua;

#endif // AS_LUA_H_
