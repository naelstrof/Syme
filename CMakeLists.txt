cmake_minimum_required( VERSION 2.8 )

set( PROJECT_NAME   "astrostruct" )
set( BIN_TARGET     "bin/${PROJECT_NAME}" )

project( ${PROJECT_NAME} )

set( CMAKE_BUILD_TYPE Debug CACHE STRING
     "Choose the type of build. Options are: None (CMAKE_CXX_FLAGS or CMAKE_C_FLAGS used), Debug, Release, RelWithDebInfo, MinSizeRel."
     FORCE )

# Linux compiler initialization.
if ( CMAKE_COMPILER_IS_GNUCXX )
    set( CMAKE_CXX_FLAGS
         "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -Werror -Wno-unused-parameter" )
         # -Wall:   Enable all warnings.
         # -Wextra: Enable some more warnings.
         # -Werror: Have errors on warnings.
         # -pedantic-errors: Error on non-standard ISO C++ code.
         # -std=c++0x: Compile C++0x code
    add_definitions( -D_CMAKE_LINUX_ )
# Windows compiler initialization.
elseif( MSVC )
    set( CMAKE_CXX_FLAGS
         "${CMAKE_CXX_FLAGS} /W4 /WX /wd4355 /wd4512" )
         # /W4: Maximum warnings.
         # /WX: Have errors on warnings.
         # /wd4355: Disable warning 4355:
         #          Using the 'this' pointer in initializer lists.
         # /wd4512: Disable warning 4512:
         #          Assignment operators NOT being able to be generated.
    add_definitions( -D_CMAKE_WINDOWS_ )
else()
    message( FATAL_ERROR "Your operating system isn't supported yet! CMake will now exit." )
endif()

# Add a check target for our makefile.
find_program( CPPCHECK_EXECUTABLE cppcheck
              DOC "A tool for static C/C++ code analysis." )
if (CPPCHECK_EXECUTABLE)
    add_custom_target( "check"
                       COMMAND "${CPPCHECK_EXECUTABLE}" "--enable=all" "*"
                       WORKING_DIRECTORY src VERBATIM )
endif()

# Add a docs target for our makefile.
find_package( Doxygen )
if ( DOXYGEN_FOUND )
    add_custom_target( "docs"
                       COMMAND "${DOXYGEN_EXECUTABLE}" "config.doxygen"
                       WORKING_DIRECTORY bin/doc VERBATIM )
endif()

# Sources
set( source
     src/game/common.cpp
     src/game/options.cpp
     src/game/config.cpp
     src/graphics/animatedsprite.cpp
     src/graphics/resource/animatedsprite.cpp
     src/graphics/resource/font.cpp
     src/graphics/lua/animatedsprite.cpp
     src/graphics/lua/animation.cpp
     src/graphics/lua/font.cpp
     src/system/lua/intrect.cpp
     src/system/lua/print.cpp
     src/system/filesystem.cpp
     src/system/fileread.cpp
     src/system/print.cpp
     src/system/lua.cpp
     src/system/window.cpp
     src/system/state.cpp
     src/system/statemachine.cpp
     src/system/resourcemanager.cpp
     src/main.cpp )

# Obtain library paths and make sure they exist.
set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmakemodules" )
find_package( SFML      REQUIRED )
find_package( Lua51     REQUIRED )
find_package( OpenGL    REQUIRED )
find_package( PHYSFS    REQUIRED )

# Includes
include_directories( ${SFML_INCLUDE_DIR}
                     ${LUA_INCLUDE_DIR}
                     ${OPENGL_INCLUDE_DIRS}
                     ${PHYSFS_INCLUDE_DIR} )

# Executable
add_executable( ${BIN_TARGET} ${source} )

# Libraries
target_link_libraries( ${BIN_TARGET}
                       ${LUA_LIBRARIES}
                       ${SFML_LIBRARY}
                       ${OPENGL_LIBRARIES}
                       ${PHYSFS_LIBRARY} )
