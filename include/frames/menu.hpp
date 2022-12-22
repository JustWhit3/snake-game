//====================================================
//     File data
//====================================================
/**
 * @file menu.hpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2022-12-22
 * @copyright Copyright (c) 2022 Gianluca Bianco under the MIT license.
 */

//====================================================
//     Preprocessor directives
//====================================================
#pragma once
#ifndef SNAKE_GAME_MENU_FRAME
#define SNAKE_GAME_MENU_FRAME

//====================================================
//     Headers
//====================================================

// Graphics
#include <SFML/Graphics.hpp>

namespace snake::frame{

    //====================================================
    //     Menu
    //====================================================
    /**
     * @brief Class used to create the main menu.
     * 
     */
    class Menu{

        // Public part
        Menu( sf::RenderWindow window );
    };
}

#endif