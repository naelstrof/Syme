#include "texture.hpp"

as::TextureResource::TextureResource( std::string path, void* data ) {
    // Just use the default constructor
    Resource( path, data );
}

as::TextureResource::load() {
    if ( m_data ) {
        return;
    }
    as::FileRead file( m_name );
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
    m_data = texture;
}

void* as::TextureResource::remove() {
    if ( !m_data ) {
        return;
    }
    delete (sf::Texture*)m_data;
}

void* as::TextureResource::copy() {
    // We should never have to copy this--
    return m_data;
}
