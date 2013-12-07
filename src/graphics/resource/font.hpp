#ifndef AS_RESOURCE_FONT_H_
#define AS_RESOURCE_FONT_H_

#include <SFML/Graphics/Font.hpp>

#include "../../system/resourcemanager.hpp"
#include "../../system/filesystem.hpp"

namespace as {

class FontResource : public Resource {
public:
    std::string     m_path;
                    FontResource( std::string name, std::string path, void* data = NULL );
                    ~FontResource();
    void            load();
    void*           copy();
    void            remove();
    char*           m_filedata;
};

}

#endif // AS_RESOURCE_FONT_H_
