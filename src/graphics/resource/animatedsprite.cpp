#include "animatedsprite.hpp"

as::AnimatedSpriteResource::AnimatedSpriteResource() : as::Resource( std::string name, void* data ) {
}

void as::AnimatedSpriteResource::load() {
    if ( (as::AnimatedSprite*)m_data->m_texture == NULL ) {
        (as::AnimatedSprite*)m_data->m_texture = (sf::Texture*)resourcemanager->getFileResource( (as::AnimatedSprite*)m_data->m_textureFileName );
    }
}

void as::AnimatedSpriteResource::remove() {
    if ( !m_data ) {
        return;
    }
    delete (as::AnimatedSprite*)m_data;
}

void* as::AnimatedSpriteResource::copy() {
    as::AnimatedSprite* sprite = new as::AnimatedSprite( m_data );
    return sprite;
}
