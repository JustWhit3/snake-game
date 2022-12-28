# Project settings
cmake_minimum_required( VERSION 3.15 )

project( snake-game-build-src
    VERSION 1.0
    DESCRIPTION "Build system for snake-game source code."
    LANGUAGES CXX
)

# Error if building out of a build directory
file( TO_CMAKE_PATH "${PROJECT_BINARY_DIR}/CMakeLists.txt" LOC_PATH )
if( EXISTS "${LOC_PATH}" )
    message( FATAL_ERROR "You cannot build in a source directory (or any directory with "
                         "CMakeLists.txt file). Please make a build subdirectory. Feel free to "
                         "remove CMakeCache.txt and CMakeFiles." )
endif()

# Set compiler options
set( CMAKE_CXX_STANDARD 20 )
set( CMAKE_CXX_STANDARD_REQUIRED ON )
set( CMAKE_CXX_EXTENSIONS OFF )

# Include directories
include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/../include )

# Creating the main executable
set( APP "snake-game" )
file( GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/../src/*.cpp )
add_executable( ${APP} ${SRC_FILES} )

# Adding specific compiler flags
if( CMAKE_CXX_COMPILER_ID STREQUAL "MSVC" )
    set( COMPILE_FLAGS "/Wall /Yd" )
else()
    set( COMPILE_FLAGS "-Wall -Wextra -pedantic -Wno-reorder" )
endif()
set( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${COMPILE_FLAGS}" )

# Adding cppcheck properties
if( CMAKE_BUILD_TYPE STREQUAL "Debug" )
    set( cppcheck cppcheck "--enable=warning" "--inconclusive" "--force" "--inline-suppr" )
    set_target_properties( ${APP} PROPERTIES CXX_CPPCHECK ${cppcheck})
endif()

# Link to SFML
find_package( SFML 2.5.1 COMPONENTS system window graphics )
target_link_libraries( ${APP} PUBLIC sfml-graphics sfml-window sfml-system )

# Link to ptc-print
find_package( ptcprint )
target_link_libraries( ${APP} PUBLIC ptcprint::ptcprint )

