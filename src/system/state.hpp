#ifndef AS_SYSTEM_STATE_H_
#define AS_SYSTEM_STATE_H_

#include <vector>
#include <string>
#include <SFML/System/Time.hpp>

#include "lua.hpp"

namespace as {

class State {
public:
                State( std::string name, int luaReference );
    void        tick( sf::Time deltaTime, lua_State* l );
    void        init( lua_State* l );
    void        exit( lua_State* l );

    std::string m_name;
    int         m_luaReference;
};

};

#endif // AS_SYSTEM_STATE_H_
