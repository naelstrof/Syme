#ifndef AS_CONFIG_H_
#define AS_CONFIG_H_

#include <string>

#include "../system/window.hpp"
#include "../system/lua.hpp"
#include "../system/print.hpp"

namespace as {

int parseConfig( std::string file, std::string pwd );

};

#endif // AS_CONFIG_H_
