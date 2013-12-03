#include "options.hpp"

int as::parseOptions( int argc, char** argv ) {
    boost::nowide::args( argc, argv );
    filesystem->m_workingDirectory = argv[0];
    return 0;
}
