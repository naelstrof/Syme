#ifndef AS_SYSTEM_SCENE_H_
#define AS_SYSTEM_SCENE_H_

#include <vector>
#include <string>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include "tickable.hpp"
#include "../system/window.hpp"

namespace as {

class Scene {
public:
    void                            draw() const;
    void                            tick( sf::Time deltaTime );
    void                            addTickable( as::Tickable* tickable );
    void                            removeTickable( as::Tickable* tickable );
    void                            addDrawable( sf::Drawable* drawable );
    void                            removeDrawable( sf::Drawable* drawable );
    void                            addLight( sf::Drawable* light );
    std::vector< as::Tickable* >    m_tickables;
    std::vector< sf::Drawable* >    m_drawables;
    std::vector< sf::Drawable* >    m_lights;
};

};

extern as::Scene* scene;

#endif // AS_SYSTEM_SCENE_H_
