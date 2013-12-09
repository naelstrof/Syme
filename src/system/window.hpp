#ifndef AS_WINDOW_H_
#define AS_WINDOW_H_

#include <SFML/Window.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RenderTexture.hpp>
#include <SFML/Graphics/Sprite.hpp>

#include "print.hpp"

namespace as {

class Window {
private:
    sf::VideoMode       m_mode;
public:
                        Window();
                        ~Window();
    std::string         m_name;
    bool                m_fullscreen;
    int                 m_videoMode;
    bool                m_noborder;
    bool                m_vsync;
    unsigned int        m_width;
    unsigned int        m_height;
    unsigned int        m_maxfps;
    int                 init();
    void                tick();
    void                printModes();
    sf::RenderWindow*   m_window;
};

};

extern as::Window* window;

#endif // AS_WINDOW_H_
