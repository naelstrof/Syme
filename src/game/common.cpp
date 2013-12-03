#include "common.hpp"

as::Common* common = new as::Common();

as::Common::Common() {
    m_running = false;
    m_deltaTime = 0;
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

    m_running = true;
    m_deltaClock.restart();
    m_gameClock.restart();
    return 0;
}

void as::Common::tick() {
    m_deltaTime = (m_deltaClock.restart()).asSeconds();
    window->tick();
    if ( !window->m_window->isOpen() ) {
        as::printf( "INF Window was closed by something, shutting down...\n" );
        m_running = false;
    }
}

float as::Common::getDeltaTime() {
    return m_deltaTime;
}
float as::Common::getGameTime() {
    return m_gameClock.getElapsedTime().asSeconds();
}
