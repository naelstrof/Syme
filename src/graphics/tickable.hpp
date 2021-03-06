#ifndef AS_GRAPHICS_TICKABLE_H_
#define AS_GRAPHICS_TICKABLE_H_

#include <SFML/System/Time.hpp>

namespace as {

class Tickable {
public:
    virtual void tick( sf::Time deltatime ) = 0;
};

};

#endif // AS_GRAPHICS_TICKABLE_H_
