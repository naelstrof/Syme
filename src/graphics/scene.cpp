#include "scene.hpp"

as::Scene* scene = new as::Scene();

void as::Scene::draw() const {
    window->m_window->clear( sf::Color::Black );
    for ( unsigned int i=0; i<m_drawables.size(); i++ ){
        window->m_window->draw( *( (sf::Drawable*)m_drawables.at( i ) ) );
    }
    window->m_window->display();
}

void as::Scene::tick( sf::Time deltaTime ) {
    for ( unsigned int i=0; i<m_drawables.size(); i++ ){
        m_drawables.at( i )->tick( deltaTime );
    }
    for ( unsigned int i=0; i<m_lights.size(); i++ ){
        m_lights.at( i )->tick( deltaTime );
    }
}

void as::Scene::addDrawable( as::Node* drawable ) {
    m_drawables.push_back( drawable );
}

void as::Scene::addLight( as::Node* light ) {
    m_lights.push_back( light );
}

void as::Scene::removeDrawable( as::Node* drawable ) {
    for ( unsigned int i=0; i<m_drawables.size(); i++ ){
        if ( m_drawables.at( i ) == drawable ) {
            m_drawables.erase( m_drawables.begin() + i );
            return;
        }
    }
}
