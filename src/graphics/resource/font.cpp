#include "font.hpp"

as::FontResource::FontResource( std::string name, std::string path, void* data ) : Resource() {
    m_name = name;
    m_path = path;
    m_data = data;
    m_filedata = NULL;
}

as::FontResource::~FontResource() {
    if ( m_filedata ) {
        delete[] m_filedata;
    }
}

void as::FontResource::load() {
    if ( m_data ) {
        return;
    }
    as::FileRead file( m_path );
    if ( !file.good() ) {
        as::printf( "ERR Couldn't find font %!\n", m_path );
        return;
    }
    m_filedata = new char[ file.size() ];
    file.read( m_filedata, file.size() );

    sf::Font* font = new sf::Font();
    bool success = font->loadFromMemory( m_filedata, file.size() );
    if ( !success ) {
        as::printf( "ERR SFML failed to load font %!\n", m_path );
    }

    //Can't delete until its no longer needed.
    //delete[] m_filedata;
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
