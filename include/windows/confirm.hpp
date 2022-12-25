//====================================================
//     File data
//====================================================
/**
 * @file confirm.hpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2022-12-16
 * @copyright Copyright (c) 2022 Gianluca Bianco under the MIT license.
 */

//====================================================
//     Preprocessor directives
//====================================================
#pragma once
#ifndef SNAKE_GAME_CONFIRM_WINDOW
#define SNAKE_GAME_CONFIRM_WINDOW

//====================================================
//     Headers
//====================================================

// SFML
#include <SFML/Window.hpp>

namespace snake::window{

    //====================================================
    //     ConfirmWindow
    //====================================================
    /**
     * @brief Class used to create the confirm window.
     * 
     */
    class ConfirmWindow: public sf::Window{

        //====================================================
        //     Public
        //====================================================
        public:

            // Constructors
            ConfirmWindow();

        //====================================================
        //     Private
        //====================================================
        private:

            // Methods
            void runWindow();

            // Constants
            const sf::VideoMode desktop{ sf::VideoMode::getDesktopMode() };
    };
}

#endif