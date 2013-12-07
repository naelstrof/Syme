#ifndef AS_RESOURCE_ANIMATEDSPRITE_H_
#define AS_RESOURCE_ANIMATEDSPRITE_H_

#include <SFML/Graphics/Texture.hpp>

#include "../../system/resourcemanager.hpp"
#include "../../system/filesystem.hpp"
#include "../animatedsprite.hpp"

namespace as {

class AnimatedSprite;

class AnimatedSpriteResource : public Resource {
public:
            AnimatedSpriteResource( std::string name, as::AnimatedSprite* data );
    void    load();
    void*   copy();
    void    remove();
};

}

#endif // AS_RESOURCE_ANIMATEDSPRITE_H_
