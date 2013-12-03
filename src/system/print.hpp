#ifndef AS_PRINT_H_
#define AS_PRINT_H_

#include <boost/nowide/iostream.hpp>

namespace as {

template<typename T, typename... Args>
int printf( const char* s, T value, Args... args );

int printf( const char* s );

};

template<typename T, typename... Args>
int as::printf( const char* s, T value, Args... args ) {
    int parses = 0;
    while ( *s ) {
        if ( *s == '%' ) {
            if ( *( s + 1 ) == '%' ) {
                s++;
            } else {
                boost::nowide::cout << value;
                parses += 1 + as::printf( s + 1, args... ); // call even when *s == 0 to detect extra arguments
                return parses;
            }
        }
        boost::nowide::cout << *s++;
        // Simulate printf's flushing on newline.
        if ( *(s - 1) == '\n' ) {
            boost::nowide::cout.flush();
        }
    }
    throw std::logic_error( "extra arguments provided to printf" );
}

#endif // AS_PRINT_H_
