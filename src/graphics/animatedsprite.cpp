#include "animatedsprite.hpp"

as::AnimatedSprite::AnimatedSprite( std::string name, std::string filename, bool paused ) :
    m_texture( NULL ),
    m_textureFileName( filename ),
    m_name( name ),
    m_paused( paused ),
    m_currentFrame( 0 ),
    m_currentAnimation( NULL ),
    m_generatedFrame( 0 ),
    m_generatedAnimation( NULL ) {
}

as::AnimatedSprite::AnimatedSprite( AnimatedSprite* ref ) :
    m_texture = ref->m_texture;
    m_textureFileName = ref->m_textureFileName;
    m_name = ref->m_name;
    m_paused = ref->m_paused;
    m_currentFrame = ref->m_currentFrame;
    m_currentAnimation = ref->m_currentAnimation;
    m_generatedFrame = ref->m_generatedFrame;
    m_generatedAnimation = ref->m_generatedAnimation;
    m_animations = ref->m_animations;
}

void as::AnimatedSprite::play() {
    m_paused = false;
}

void as::AnimatedSprite::stop() {
    setFrame( 0 );
}

void as::AnimatedSprite::play( std::string name ) {
    for ( unsigned int i=0; i<m_animations.size(); i++ ) {
        if ( m_animations.at( i ).m_name == name ) {
            m_currentAnimation = &( m_animations.at( i ) );
            m_currentTime = sf::Time::Zero;
            m_currentFrame = 0;
            break;
        }
    }
}

void as::AnimatedSprite::setFrame( unsigned int frameIndex ) {
    m_currentFrame = frameIndex;
    // Only change the current time if we'll actually be using it.
    if ( m_currentAnimation.m_fps == 0 ) {
        return;
    }
    m_currentTime = sf::Time::seconds( float( frameIndex ) / m_currentAnimation.m_fps );
}

void as::AnimatedSprite::tick( sf::Time deltaTime ) {
    // if paused or we have less than one frame to display on the current animation.
    if ( m_paused || m_currentAnimation.m_frames.size() <= 1 ) {
        return;
    }
    m_currentTime += deltaTime;
    updateFrameIndex();
    updateFrame();
}

void as::AnimatedSprite::updateFrameIndex() {
    if ( m_currentAnimation.m_fps == 0 ) {
        return;
    }
    m_currentFrame = m_currentTime.asSeconds() * m_currentAnimation.m_fps;
    // Loop through the frames.
    if ( m_currentAnimation.m_loop ) {
        m_currentFrame = fmod( frame, m_currentAnimation.m_frames.size() - 1 );
    } else {
        if ( m_currentFrame >= m_currentAnimation.m_frames.size() - 1 ) {
            m_currentFrame = m_currentAnimation.size() - 1;
            m_paused = true;
        }
    }
}

void as::AnimatedSprite::updateFrame() {
    // If we already generated this frame, ignore the request to update it.
    if ( m_currentFrame == m_generatedFrame && m_currentAnimation == m_generatedAnimation ) {
        return;
    }
    m_generatedFrame = m_currentFrame;
    m_generatedAnimation = m_currentAnimation;
    sf::IntRect rect = m_currentAnimation.m_frames.at( m_currentFrame );
    float x = float( rect.width ) / 2.f;
    float y = float( rect.width ) / 2.f;
    m_vertices[0].position = sf::Vector2f( -x, -y );
    m_vertices[1].position = sf::Vector2f( -x, y );
    m_vertices[2].position = sf::Vector2f( x, y );
    m_vertices[3].position = sf::Vector2f( x, -y );
    float left = float( rect.left ) + 0.0001f;
    float right = left + float( rect.width );
    float top = float( rect.top );
    float bottom = top + float( rect.height );
    m_vertices[0].texCoords = sf::Vector2f( left, top );
    m_vertices[1].texCoords = sf::Vector2f( left, bottom );
    m_vertices[2].texCoords = sf::Vector2f( right, bottom );
    m_vertices[3].texCoords = sf::Vector2f( right, top );
}

void as::AnimatedSprite::draw( sf::RenderTarget* target, sf::RenderStates states ) {
    if ( !( m_currentAnimation && m_currentAnimation.m_texture ) ) {
        return;
    }
    if ( m_texture == NULL ) {
        m_texture = texturemanager->get( filename );
    }
    states.transform *= getTransform();
    states.texture = m_texture;
    target.draw( m_verticies, 4, sf::Quads, states );
}
