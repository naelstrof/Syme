#ifndef AS_SYSTEM_SCENE_H_
#define AS_SYSTEM_SCENE_H_

#include <vector>
#include <string>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include "tickable.hpp"
#include "animatedsprite.hpp"
#include "../system/window.hpp"

namespace as {

class Scene {
public:
    void                            draw() const;
    void                            tick( sf::Time deltaTime );
    void                            add( as::AnimatedSprite* object );
    void                            remove( void* object );
    std::vector< as::Tickable* >    m_tickables;
    std::vector< sf::Drawable* >    m_drawables;
};

};

extern as::Scene* scene;

#endif // AS_SYSTEM_SCENE_H_
