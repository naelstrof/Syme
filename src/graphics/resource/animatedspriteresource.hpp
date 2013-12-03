#ifndef AS_ANIMATEDSPRITERESOURCE_H_
#define AS_ANIMATEDSPRITERESOURCE_H_

#include <SFML/Graphics/Texture.hpp>

#include "../../system/resourcemanager.hpp"

namespace as {

class AnimatedSpriteResource : Resource {
public:
    void    load();
    void*   copy();
    void    remove();
};

}

#endif // AS_TEXTURERESOURCE_H_
