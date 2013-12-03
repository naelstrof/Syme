#include "filesystem.hpp"

as::FileSystem* filesystem = new as::FileSystem();

as::FileSystem::FileSystem() {
    // This is set by as::parseOptions, since the pwd resides in the first argument of the provided options.
    m_workingDirectory = "";
}

as::FileSystem::~FileSystem() {
    PHYSFS_deinit();
}

void as::FileSystem::checkError() {
    const char* errmsg = PHYSFS_getLastError();
    if ( errmsg ) {
        as::printf( "ERR %\n", errmsg );
    }
}

int as::FileSystem::init() {
    int err = PHYSFS_init( m_workingDirectory.c_str() );
    // Returns non-zero on success-- whyyyyyy
    if ( !err ) {
        as::printf( "ERR Couldn't initialize PHYSFS at location: %\n", m_workingDirectory );
        checkError();
        return 1;
    }

    // Print off the version of PHYSFS we're using.
    PHYSFS_Version compiled;
    PHYSFS_Version linked;

    PHYSFS_VERSION( &compiled );
    PHYSFS_getLinkedVersion( &linked );
    // Ew, I thought my custom c++ enabled printf would make everything cleaner. Guess not.
    as::printf( "INF PHYSFS compiled version: %.%.%\n", (unsigned int)compiled.major, (unsigned int)compiled.minor, (unsigned int)compiled.patch );
    as::printf( "INF PHYSFS linked   version: %.%.%\n", (unsigned int)linked.major, (unsigned int)linked.minor, (unsigned int)linked.patch );

    // This should never be enabled, it's a huge security flaw otherwise.
    PHYSFS_permitSymbolicLinks( false );
    // Creates a sane configuraton where written files are saved to ~/.invictus/astrostruct and scans for .zip files named as .pak in the base directory to add to the game data.
    PHYSFS_setSaneConfig( "invictus", "astrostruct", "zip", 0, 0 );

    // Here we'll print out some handy information:
    as::printf( "INF PHYSFS supported archives are: " );
    const PHYSFS_ArchiveInfo** listing = PHYSFS_supportedArchiveTypes();
    as::printf( "%", listing[0]->extension );
    int i = 1;
    while ( listing[i] != NULL ) {
        as::printf( ", %", listing[i]->extension );
        i++;
    }
    as::printf( ".\n" );
    return 0;
}

void as::FileSystem::tick() {
    checkError();
}

std::vector<std::string> as::FileSystem::getFiles( std::string dir, bool recursive ) {
    std::vector<std::string> files;
    if ( !exists( dir ) ) {
        return files;
    }

    char** list = PHYSFS_enumerateFiles( dir.c_str() );
    int i = 0;
    while ( list[i] != NULL ) {
        std::string file = dir + '/' + std::string( list[i] );
        files.push_back( file );
        if ( recursive && PHYSFS_isDirectory( file.c_str() ) ) {
            std::vector<std::string> newfiles = getFiles( file );
            files.insert( files.end(), newfiles.begin(), newfiles.end() );
        }
        i++;
    }
    PHYSFS_freeList( list );
    return files;
}

bool as::FileSystem::exists( std::string dir ) {
    return PHYSFS_exists( dir.c_str() );
}

bool as::FileSystem::isDirectory( std::string dir ) {
    return PHYSFS_isDirectory( dir.c_str() );
}
