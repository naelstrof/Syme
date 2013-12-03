#ifndef AS_ANIMATION_H_
#define AS_ANIMATION_H_

#include <vector>
#include <SFML/Graphics/Rect.hpp>

namespace as {

class Animation {
public:
    std::vector<sf::IntRect>    m_frames;
    std::string                 m_name;
    bool                        m_loop;
    float                       m_fps;
};

};

#endif  // AS_ANIMATION_H_
