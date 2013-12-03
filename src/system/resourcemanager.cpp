#include "resourcemanager.hpp"

as::Resource::Resource( std::string name, void* data ) :
    m_name( name ),
    m_data( data ) {
}

as::Resource::load() {
    // Do nothing since we're supposed to be polymorphed
    //if ( m_data ) {
        //return;
    //}
}

as::Resource::remove() {
    // Do nothing since we're supposed to be polymorphed
}

as::ResourceManager::~ResourceManager() {
    for ( unsigned int i=0; i<m_fileResources.size(); i++ ) {
        m_fileResources.at( i ).remove();
    }
    for ( unsigned int i=0; i<m_processedResources.size(); i++ ) {
        m_processedResources.at( i ).remove();
    }
}

void as::ResourceManager::addFileResource( Resource* resource ) {
    m_fileResources.push_back( resource );
}

void as::ResourceManager::addProcessedResource( Resource* resource ) {
    m_processedResources.push_back( resource );
}

// TODO: Since this will be called a lot, it may be smart to make a binary search based on the first character of the paths.
as::Resource* as::ResourceManager::getFileResource( std::string path, std::string type ) {
    for ( unsigned int i=0; i<m_fileResources.size(); i++ ) {
        if ( m_fileResources.at( i ).m_name == path && typeid( *( m_fileResources.at( i ) ) ).name() == type ) {
            // The resource is needed, so actually prepare it right now if it hasn't been prepped already.
            m_fileResources.at( i )->load();
            return m_fileResources.at( i ).m_data;
        }
    }
}

void* as::ResourceManager::getProcessedResource( std::string name, std::string type ) {
    for ( unsigned int i=0; i<m_processedResources.size(); i++ ) {
        if ( m_fileResources.at( i ).m_name == name && typeid( *( m_fileResources.at( i ) ) ).name() == type ) {
            // The resource is needed, so actually prepare it right now if it hasn't been prepped already.
            m_fileResources.at( i )->load();
            // Processed resources must be copied to be used.
            return m_fileResources.at( i ).copy();
        }
    }
}
