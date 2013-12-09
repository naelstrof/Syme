#include "animation.hpp"

as::Animation::Animation( std::string name, float fps, bool loop ) :
    m_name( name ),
    m_fps( fps ),
    m_loop( loop ) {
}

void as::Animation::addFrame( sf::IntRect intrect ) {
    m_frames.push_back( intrect );
}
