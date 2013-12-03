#include "animatedspriteresource.hpp"

as::AnimatedSpriteResource::load() {
    // Don't have to load anything :)
}

void* as::AnimatedSpriteResource::remove() {
    if ( !m_data ) {
        return;
    }
    delete (as::AnimatedSprite*)m_data;
}

void* as::AnimatedSpriteResource::copy() {
    as::AnimatedSprite* sprite = new as::AnimatedSprite( m_data );
    return sprite;
}
