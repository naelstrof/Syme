#ifndef AS_ANIMATEDSPRITE_H_
#define AS_ANIMATEDSPRITE_H_

#include <vector>
#include <string>
#include <cmath>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Vector2.hpp>

namespace as {

class AnimatedSprite : public sf::Drawable, public sf::Transformable {
public:
                                AnimatedSprite( std::string name, bool paused = false );
                                AnimatedSprite( AnimatedSprite* ref );
    std::vector<as::Animation>  m_animations;
    as::Animation*              m_currentAnimation;
    as::Animation*              m_generatedAnimation;
    std::string                 m_name;
    bool                        m_paused;
    unsigned int                m_currentFrame;
    unsigned int                m_generatedFrame;
    void                        setFrame( unsigned int frameIndex );
    void                        play( std::string name );
    void                        pause();
    void                        stop();
    sf::Time                    m_currentTime;
    sf::Texture*                m_texture;
    std::string                 m_textureFileName;
private:
    void                        updateFrameIndex();
    void                        updateFrame();
};

};

#endif // AS_ANIMATEDSPRITE_H_
