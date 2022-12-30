//====================================================
//     File data
//====================================================
/**
 * @file gui.hpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2022-12-30
 * @copyright Copyright (c) 2022 Gianluca Bianco under the MIT license.
 */

//====================================================
//     Headers
//====================================================

// SFML
#include <SFML/Window/VideoMode.hpp>

//====================================================
//     Preprocessor directives
//====================================================
#pragma once
#ifndef SNAKE_GAME_GUI_UTILITY
#define SNAKE_GAME_GUI_UTILITY

namespace snake::utility{

    // Functions
    extern sf::VideoMode getDesktopMode();
}

#endif