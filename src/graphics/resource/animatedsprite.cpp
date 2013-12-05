#include "animatedsprite.hpp"

as::AnimatedSpriteResource::AnimatedSpriteResource( std::string name, as::AnimatedSprite* data ) : as::Resource() {
    m_name = name;
    m_data = data;
}

void as::AnimatedSpriteResource::load() {
    as::AnimatedSprite* sprite = (as::AnimatedSprite*)m_data;
    if ( sprite->m_texture == NULL ) {
        sprite->m_texture = (sf::Texture*)resourcemanager->getFileResource( sprite->m_textureFileName );
    }
}

void as::AnimatedSpriteResource::remove() {
    if ( !m_data ) {
        return;
    }
    delete (as::AnimatedSprite*)m_data;
}

void* as::AnimatedSpriteResource::copy() {
    as::AnimatedSprite* sprite = new as::AnimatedSprite( (as::AnimatedSprite*)m_data );
    return sprite;
}
