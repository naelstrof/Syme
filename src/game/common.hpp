#ifndef AS_COMMON_H_
#define AS_COMMON_H_

#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>

#include "../system/print.hpp"
#include "../system/filesystem.hpp"
#include "../system/window.hpp"
#include "../system/lua.hpp"

namespace as {

class Common {
private:
    sf::Clock   m_deltaClock;
    sf::Clock   m_gameClock;
    sf::Time    m_deltaTime;
public:
                Common();
                ~Common();
    int         init();
    void        tick();
    bool        m_running;
    float       getGameTime();
    sf::Time    getDeltaTime();
    as::AnimatedSprite* m_sprite;
    sf::Text    m_text;
};

};

extern as::Common* common;

#endif // AS_COMMON_H_
