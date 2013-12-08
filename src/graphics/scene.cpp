#include "scene.hpp"

as::Scene* scene = new as::Scene();

void as::Scene::draw() const {
    window->m_window->clear( sf::Color::Black );
    for ( unsigned int i=0; i<m_drawables.size(); i++ ){
        window->m_window->draw( *m_drawables.at( i ) );
    }
    window->m_window->display();
}

void as::Scene::tick( sf::Time deltaTime ) {
    for ( unsigned int i=0; i<m_tickables.size(); i++ ){
        if ( m_tickables.at( i ) != NULL ) {
            // This horrible one-liner just casts the void* into a as::Tickable* and runs tick( deltaTime ) on it.
            m_tickables.at( i )->tick( deltaTime );
        }
    }
}

void as::Scene::add( as::AnimatedSprite* object ) {
    m_drawables.push_back( object );
    m_tickables.push_back( object );
}

void as::Scene::remove( void* object ) {
    for ( unsigned int i=0; i<m_drawables.size(); i++ ) {
        if ( m_drawables.at( i ) == object ) {
            m_drawables.erase( m_drawables.begin() + i );
            m_tickables.erase( m_tickables.begin() + i );
        }
    }
}

/*void as::Scene::addLight( as::Node* light ) {
    m_lights.push_back( light );
}*/
