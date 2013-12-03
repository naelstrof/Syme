#include "window.hpp"

as::Window* window = new as::Window();

as::Window::Window() {
    m_name = "Astrostruct";
    m_fullscreen = false;
    m_noborder = true;
    m_videoMode = 0;
    m_width = 640;
    m_height = 480;
    m_vsync = true;
    m_maxfps = 300;
    m_window = new sf::RenderWindow();
}

int as::Window::init() {
    // First figure out what kind of mode we're in.
    switch ( m_videoMode ) {
        // Use provided width and height.
        case -1: {
            m_mode = sf::VideoMode( m_width, m_height );
            break;
        }
        // Use desktop width and height.
        case 0: {
            m_mode = sf::VideoMode::getDesktopMode();
            break;
        }
        // Use provided video mode.
        default: {
            int modeIndex = m_videoMode--;
            std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();
            if ( modeIndex < (int)modes.size() && modeIndex >= 0 ) {
                m_mode = modes.at( modeIndex );
            } else {
                as::printf( "ERR Video mode index % is out of range, using last available video mode...\n", m_videoMode );
                m_mode = modes.back();
            }
            break;
        }
    }
    printModes();
    if ( m_fullscreen && !m_mode.isValid() ) {
        as::printf( "WRN %x% is an invalid video mode!\n", m_width, m_height );
        as::printf( "INF Using desktop resolution instead.\n" );
        m_mode = sf::VideoMode::getDesktopMode();
    }
    if ( m_noborder ) {
        m_window->create( m_mode, m_name, sf::Style::None );
    } else if ( m_fullscreen ) {
        m_window->create( m_mode, m_name, sf::Style::Fullscreen );
    } else {
        m_window->create( m_mode, m_name );
    }
    m_window->setFramerateLimit( m_maxfps );
    m_window->setVerticalSyncEnabled( m_vsync );
    return 0;
}

void as::Window::printModes() {
    as::printf( "INF Available Video modes: (Only showing highest bits per pixel)\n" );
    std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();
    unsigned int highestBit = 0;
    for ( unsigned int i=0;i<modes.size();i++ ) {
        if ( modes[i].bitsPerPixel >= highestBit ) {
            as::printf( "INF\tID: %\tWidth: %\tHeight: %\tBits: %\n", i, modes[i].width, modes[i].height, modes[i].bitsPerPixel );
            highestBit = modes[i].bitsPerPixel;
        }
    }
}

void as::Window::tick() {
    if ( !m_window->isOpen() ) {
        return;
    }
    sf::Event event;
    while ( m_window->pollEvent( event ) ) {
        switch ( event.type ) {
            case sf::Event::Closed: {
                m_window->close();
                break;
            }
            //case sf::Event::Resized: {
                //glViewport( 0, 0, event.size.width, event.size.height );
                //break;
            //}
            //case sf::Event::LostFocus: {
                //m_focus = false;
                //break;
            //}
            //case sf::Event::GainedFocus: {
                //m_focus = true;
                //break;
            //}
            //case sf::Event::TextEntered: {
                //keyboard->addInput( event.text.unicode );
                //break;
            //}
            //case sf::Event::KeyPressed: {}
            //case sf::Event::KeyReleased: {}
            //case sf::Event::MouseWheelMoved: {}
            //case sf::Event::MouseButtonPressed: {}
            //case sf::Event::MouseButtonReleased: {}
            //case sf::Event::MouseMoved: {}
            //case sf::Event::MouseEntered: {}
            //case sf::Event::MouseLeft: {}
            //case sf::Event::JoystickButtonPressed: {}
            //case sf::Event::JoystickButtonReleased: {}
            //case sf::Event::JoystickMoved: {}
            //case sf::Event::JoystickConnected: {}
            //case sf::Event::JoystickDisconnected: {}
            //case sf::Event::Count: {}
            default: {
                break;
            }
        }
    }
}
