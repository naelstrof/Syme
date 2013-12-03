#include "print.hpp"

int as::printf( const char* s ) {
    boost::nowide::cout << s;
    return 0;
}
