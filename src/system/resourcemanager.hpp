// Handles loading any kind of resource, there's two kinds of resources defined: a file resource and a processed resource. Processed resources will be things like as::AnimatedSprite which when grabbed will need a new copy of itself to keep track of individual animations. While file resources are ones that won't change, but can be referenced by many processed resources. For example two different AnimatedSprites may reference the same texture, and as such the texture will only be loaded once and be given to both AnimatedSprites. This avoids the possiblity of redundancy as well as makes resource loading a little more effecient.
#ifndef AS_RESOURCEMANAGER_H_
#define AS_RESOURCEMANAGER_H_

#include <vector>
#include <string>
//#include <typeinfo>
#include "print.hpp"

namespace as {

class Resource {
public:
                    Resource();
                    Resource( std::string name, void* data = NULL );
    virtual         ~Resource();
    std::string     m_name;
    void*           m_data;
    virtual void    load();
    virtual void*   copy();
    virtual void    remove();
};

class ResourceManager {
public:
    ~ResourceManager();
    std::vector<as::Resource*>  m_resources;
    void                        addResource( Resource* resource );
    void*                       getResource( std::string path );
};

};

extern as::ResourceManager* resourcemanager;

#endif // AS_RESOURCEMANAGER_H_
