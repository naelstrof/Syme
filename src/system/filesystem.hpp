#ifndef AS_FILESYSTEM_H_
#define AS_FILESYSTEM_H_

#include <physfs.h>
#include <string>
#include <vector>

#include "print.hpp"
#include "fileread.hpp"

namespace as {

class FileSystem {
private:
    void                        checkError();
public:
    FileSystem();
    ~FileSystem();
    int                         init();
    void                        tick();
    std::vector<std::string>    getFiles( std::string dir, bool recursive = true);
    bool                        exists( std::string dir );
    bool                        isDirectory( std::string dir );
    std::string                 m_workingDirectory;
};

};

extern as::FileSystem* filesystem;

#endif // IS_FILESYSTEM_H_
