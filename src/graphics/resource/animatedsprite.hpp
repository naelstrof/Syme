#ifndef AS_ANIMATEDSPRITE_H_
#define AS_ANIMATEDSPRITE_H_

#include <SFML/Graphics/Texture.hpp>

#include "../animatedsprite.hpp"
#include "../../system/resourcemanager.hpp"

namespace as {

class AnimatedSprite;

class AnimatedSpriteResource : public Resource {
public:
            AnimatedSpriteResource();
    void    load();
    void*   copy();
    void    remove();
};

}

#endif // AS_ANIMATEDSPRITE_H_
