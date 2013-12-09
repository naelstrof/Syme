#ifndef AS_ENGINE_H_
#define AS_ENGINE_H_

#include "game/common.hpp"
#include "game/config.hpp"
#include "game/options.hpp"

namespace as {

// Evertything globally initializes itself, so we must clean up after everything.
void cleanUp() {
    delete common;
    delete lua;
    delete resourcemanager;
    delete statemachine;
    delete filesystem;
    delete window;
    delete scene;
}

};

#endif // AS_ENGINE_H_
