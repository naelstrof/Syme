#ifndef AS_FILEREAD_H_
#define AS_FILEREAD_H_

#include "print.hpp"
#include "filesystem.hpp"

namespace as {

class FileRead {
public:
                    FileRead( std::string dir );
                    ~FileRead();
    void            close();
    bool            good();
    unsigned int    read( void* buffer, unsigned int size );
    unsigned int    size();
private:
    bool m_open;
    bool m_exists;
    bool m_eof;
    PHYSFS_File* m_file;
};

};

#endif // AS_FILEREAD_H_
