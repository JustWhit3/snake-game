//====================================================
//     File data
//====================================================
/**
 * @file game.hpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2022-12-19
 * @copyright Copyright (c) 2022 Gianluca Bianco under the MIT license.
 */

//====================================================
//     Preprocessor directives
//====================================================
#pragma once
#ifndef SNAKE_GAME_GAME_WINDOW
#define SNAKE_GAME_GAME_WINDOW

//====================================================
//     Headers
//====================================================

// SFML
#include <SFML/Graphics.hpp>

namespace snake::window{

    //====================================================
    //     GameWindow
    //====================================================
    /**
     * @brief Class used to create the game window. 
     * 
     */
    class GameWindow: public sf::RenderWindow{

        //====================================================
        //     Public
        //====================================================
        public:

            // Constructors
            GameWindow();

            // Methods
            void runWindow();

            // Variables
            sf::Color background_color{ sf::Color::White };

        //====================================================
        //     Private
        //====================================================
        private:

            // Constants
            const sf::VideoMode desktop{ sf::VideoMode::getDesktopMode() };
    };
}

#endif