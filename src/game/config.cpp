#include "config.hpp"

int as::parseConfig( std::string file, std::string pwd ) {
    // Failsafe for the filesystem initialization, in case parseOptions is never ran.
    filesystem->m_workingDirectory = pwd;
    // FIXME: This will probably only work on Linux since windows uses \ instead of /.
    // Make it so we can actually find the file, no matter what the working directory is.
    std::string actualFile = pwd.substr( 0, pwd.find_last_of( '/' ) + 1 ) + file;
    // We can't use the actual lua->doFile since the filesystem isn't initialized yet.
    if ( luaL_dofile( lua->m_l, actualFile.c_str() ) ) {
        std::string error = lua_tostring( lua->m_l, -1 );
        as::printf( "ERR %\n", error );
        as::printf( "ERR failed to execute configuration file %, using default configuration.\n", file );
        return 1;
    }
    // The configuration file should have a table named Configuration within it
    lua_getglobal( lua->m_l, "Configuration" );
    float number;
    bool boolean;

    // Parse window options
    if ( !lua->getNumber( lua->m_l, "WindowCustomWidth", &number ) ) {
        if ( number < 0 ) {
            number = 0;
        }
        window->m_width = (unsigned int)number;
    }
    if ( !lua->getNumber( lua->m_l, "WindowCustomHeight", &number ) ) {
        if ( number < 0 ) {
            number = 0;
        }
        window->m_height = (unsigned int)number;
    }
    if ( !lua->getNumber( lua->m_l, "WindowVideoMode", &number ) ) {
        window->m_videoMode = (int)number;
    }
    if ( !lua->getBool( lua->m_l, "WindowFullscreen", &boolean ) ) {
        window->m_fullscreen = boolean;
    }
    if ( !lua->getBool( lua->m_l, "WindowNoBorder", &boolean ) ) {
        window->m_noborder = boolean;
    }

    lua_pop( lua->m_l, 1 );

    return 0;
}
