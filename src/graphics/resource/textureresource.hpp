#ifndef AS_TEXTURERESOURCE_H_
#define AS_TEXTURERESOURCE_H_

#include <SFML/Graphics/Texture.hpp>

#include "../../system/resourcemanager.hpp"
#include "../../system/filesystem.hpp"

namespace as {

class TextureResource : Resource {
public:
    void    load();
    void*   copy();
    void    remove();
};

}

#endif // AS_TEXTURERESOURCE_H_
