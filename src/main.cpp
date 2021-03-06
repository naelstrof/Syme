#include "engine.hpp"

int main( int argc, char** argv ) {
    // Parse lua configuration first, so command line options override it.
    as::parseConfig( "init.lua", argv[0] );
    as::parseOptions( argc, argv );
    common->init();
    as::printf( "INF Welcome to Astrostruct.\n" );
    while ( common->m_running ) {
        common->tick();
    }
    as::cleanUp();
    return 0;
}
