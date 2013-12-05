#include "font.hpp"

as::FontResource::FontResource( std::string name, std::string path, void* data ) {
    m_name = name;
    m_path = path;
    m_data = data;
}

void as::FontResource::load() {
    if ( m_data ) {
        return;
    }
    as::FileRead file( m_name );
    if ( !file.good() ) {
        as::printf( "ERR Couldn't find font %!\n", m_name );
        return;
    }
    char* data = new char[ file.size() ];
    file.read( data, file.size() );

    sf::Font* font = new sf::Font();
    bool success = font->loadFromMemory( data, file.size() );
    if ( !success ) {
        as::printf( "ERR SFML failed to load font %!\n", m_name );
    }

    delete[] data;
    m_data = font;
}

void as::FontResource::remove() {
    if ( !m_data ) {
        return;
    }
    delete (sf::Font*)m_data;
}

void* as::FontResource::copy() {
    // We should never have to copy this--
    return m_data;
}
