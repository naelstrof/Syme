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

#include "animation.hpp"
#include "resource/animatedsprite.hpp"
#include "../system/resourcemanager.hpp"
#include "tickable.hpp"

namespace as {

class AnimatedSprite : public sf::Drawable, public sf::Transformable, as::Tickable {
public:
    explicit                    AnimatedSprite( std::string name, std::string filename, bool paused = false );
                                AnimatedSprite( AnimatedSprite* ref );
                                ~AnimatedSprite();
    void                        setFrame( unsigned int frameIndex );
    void                        play( std::string name );
    void                        play();
    void                        pause();
    void                        stop();
    void                        tick( sf::Time deltaTime );
    void                        addAnimation( as::Animation* animation );
    virtual void                draw( sf::RenderTarget& target, sf::RenderStates states ) const;

    sf::Texture*                m_texture;
    std::string                 m_textureFileName;
    std::string                 m_name;
    bool                        m_paused;
    as::Animation*              m_currentAnimation;
    as::Animation*              m_generatedAnimation;
    unsigned int                m_currentFrame;
    unsigned int                m_generatedFrame;
    sf::Time                    m_currentTime;
    std::vector<as::Animation>  m_animations;
private:
    void                        updateFrameIndex();
    void                        updateFrame();
    sf::Vertex m_vertices[4];
};

};

#endif // AS_ANIMATEDSPRITE_H_
