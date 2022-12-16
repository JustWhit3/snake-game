# Project settings
cmake_minimum_required( VERSION 3.15 )

project( snake-game-build
    VERSION 1.0
    DESCRIPTION "Build system for snake-game."
    LANGUAGES CXX
)

# Error if building out of a build directory
file( TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH )
if( EXISTS "${LOC_PATH}" )
    message( FATAL_ERROR "You cannot build in a source directory (or any directory with "
                         "CMakeLists.txt file). Please make a build subdirectory. Feel free to "
                         "remove CMakeCache.txt and CMakeFiles." )
endif()

# Fetching deps
add_subdirectory( deps )

# Compiling the main app
add_subdirectory( src )