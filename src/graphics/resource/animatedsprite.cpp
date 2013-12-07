#include "animatedsprite.hpp"

as::AnimatedSpriteResource::AnimatedSpriteResource( std::string name, as::AnimatedSprite* data ) : as::Resource() {
    m_name = name;
    m_data = data;
}

void as::AnimatedSpriteResource::load() {
    as::AnimatedSprite* sprite = (as::AnimatedSprite*)m_data;
    if ( sprite->m_texture == NULL ) {
        as::FileRead file( sprite->m_textureFileName );
        if ( !file.good() ) {
            as::printf( "ERR Couldn't find texture %!\n", m_name );
            return;
        }
        char* data = new char[ file.size() ];
        file.read( data, file.size() );

        sf::Texture* texture = new sf::Texture();
        bool success = texture->loadFromMemory( data, file.size() );
        texture->setSmooth( true );
        if ( !success ) {
            as::printf( "ERR SFML failed to load texture %! It will appear black.\n", m_name );
        }

        delete[] data;
        sprite->m_texture = texture;
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
