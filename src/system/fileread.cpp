#include "fileread.hpp"

// Must be valid utf-8!
as::FileRead::FileRead( std::string dir ) {
    m_open = false;
    m_exists = filesystem->exists( dir );
    if ( m_exists ) {
        m_file = PHYSFS_openRead( dir.c_str() );
        if ( !m_file ) {
            std::string absolutedir = PHYSFS_getRealDir( dir.c_str() );
            as::printf( "ERR %/%: %", absolutedir, dir, PHYSFS_getLastError());
            return;
        }
        m_eof = PHYSFS_eof( m_file );
        m_open = true;
    } else {
        as::printf( "ERR File % does not exist!\n", dir );
    }
}

as::FileRead::~FileRead() {
    close();
}

unsigned int as::FileRead::read( void* buffer, unsigned int size ) {
    if ( !good() ) {
        return 0;
    }
    return PHYSFS_read( m_file, buffer, 1, size );
}

unsigned int as::FileRead::size() {
    if ( !m_exists ) {
        return 0;
    }
    return PHYSFS_fileLength( m_file );
}

void as::FileRead::close() {
    if (m_file)
    {
        PHYSFS_close(m_file);
    }
    m_open = false;
}

bool as::FileRead::good() {
    if ( m_exists ) {
        m_eof = PHYSFS_eof( m_file );
    }
    return ( m_open && m_exists && ~m_eof && m_file );
}
