#ifndef AS_RESOURCE_TEXTURE_H_
#define AS_RESOURCE_TEXTURE_H_

#include <SFML/Graphics/Texture.hpp>

#include "../../system/resourcemanager.hpp"
#include "../../system/filesystem.hpp"

namespace as {

class TextureResource : public Resource {
public:
            TextureResource( std::string path, void* data = NULL );
    void    load();
    void*   copy();
    void    remove();
};

}

#endif // AS_RESOURCE_TEXTURE_H_
