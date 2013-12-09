#ifndef AS_ANIMATION_H_
#define AS_ANIMATION_H_

#include <vector>
#include <SFML/Graphics/Rect.hpp>

namespace as {

class Animation {
public:
    Animation( std::string name, float fps, bool loop );
    void addFrame( sf::IntRect intrect );
    std::string                 m_name;
    float                       m_fps;
    bool                        m_loop;
    std::vector<sf::IntRect>    m_frames;
};

};

#endif  // AS_ANIMATION_H_
