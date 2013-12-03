#ifndef AS_COMMON_H_
#define AS_COMMON_H_

#include <SFML/System/Clock.hpp>

#include "../system/print.hpp"
#include "../system/filesystem.hpp"
#include "../system/window.hpp"

namespace as {

class Common {
private:
    sf::Clock   m_deltaClock;
    sf::Clock   m_gameClock;
    double      m_deltaTime;
public:
                Common();
                ~Common();
    int         init();
    void        tick();
    bool        m_running;
    float       getGameTime();
    float       getDeltaTime();
};

};

extern as::Common* common;

#endif // AS_COMMON_H_
