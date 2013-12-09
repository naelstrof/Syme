#include "resourcemanager.hpp"

as::ResourceManager* resourcemanager = new as::ResourceManager();

as::Resource::Resource() {
}

as::Resource::Resource( std::string name, void* data ) :
    m_name( name ),
    m_data( data ) {
}

as::Resource::~Resource() {
}

void as::Resource::load() {
    // Do nothing since we're supposed to be polymorphed
    //if ( m_data ) {
        //return;
    //}
}

void as::Resource::remove() {
    // Do nothing since we're supposed to be polymorphed
}

void* as::Resource::copy() {
    // Do nothing since we're supposed to be polymorphed
    return NULL;
}

as::ResourceManager::~ResourceManager() {
    for ( unsigned int i=0; i<m_resources.size(); i++ ) {
        m_resources.at( i )->remove();
    }
}

void as::ResourceManager::addResource( Resource* resource ) {
    m_resources.push_back( resource );
}

// TODO: Since this will be called a lot, it may be smart to make a binary search based on the first character of the paths.
void* as::ResourceManager::getResource( std::string path ) {
    for ( unsigned int i=0; i<m_resources.size(); i++ ) {
        if ( m_resources.at( i )->m_name == path ) {
            // The resource is needed, so actually prepare it right now if it hasn't been prepped already.
            m_resources.at( i )->load();
            return m_resources.at( i )->copy();
        }
    }
    as::printf( "ERR Couldn't find resource %!\n", path );
    return NULL;
}
