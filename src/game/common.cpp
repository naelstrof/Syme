#include "common.hpp"

as::Common* common = new as::Common();

as::Common::Common() {
    m_running = false;
    m_deltaTime = sf::Time::Zero;
    m_sprite = NULL;
}

as::Common::~Common() {
    delete filesystem;
    delete window;
    delete lua;
}

int as::Common::init() {
    int err = filesystem->init();
    if ( err ) {
        as::printf( "ERR Failed initialize the filesystem, shutting down...\n" );
        return err;
    }

    err = window->init();
    if ( err ) {
        as::printf( "ERR Failed to open a window, shutting down...\n" );
        return err;
    }

    err = lua->init();
    if ( err ) {
        as::printf( "ERR Failed to initialize Lua, shutting down...\n" );
        return err;
    }

    lua->doFolder( "data/textures" );

    m_text.setFont( *(sf::Font)resourcemanager->getResource( "gui" ) );
    m_text.setString( "w0w" );
    m_sprite = (as::AnimatedSprite*)resourcemanager->getResource( "t_foob" );
    m_sprite->setPosition( window->m_window->getSize().x/2.f, window->m_window->getSize().y/2.f);

    m_running = true;
    m_deltaClock.restart();
    m_gameClock.restart();
    return 0;
}

void as::Common::tick() {
    m_deltaTime = m_deltaClock.restart();
    window->tick();
    if ( !window->m_window->isOpen() ) {
        as::printf( "INF Window was closed by something, shutting down...\n" );
        m_running = false;
        return;
    }
    window->m_window->clear( sf::Color::Black );
    window->m_window->draw( *m_sprite );
    window->m_window->draw( m_text );
    window->m_window->display();
    m_sprite->tick( m_deltaTime );
    m_sprite->rotate( m_deltaTime.asSeconds() * 100 );
    m_sprite->setScale( m_gameClock.getElapsedTime().asSeconds(), m_gameClock.getElapsedTime().asSeconds() );
}

sf::Time as::Common::getDeltaTime() {
    return m_deltaTime;
}
float as::Common::getGameTime() {
    return m_gameClock.getElapsedTime().asSeconds();
}
