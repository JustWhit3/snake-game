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
#ifndef SNAKE_GAME_MENU_STATE
#define SNAKE_GAME_MENU_STATE

//====================================================
//     Headers
//====================================================

// Windows
#include <windows/game.hpp>

// States
#include <states/state.hpp>

// SFML
#include <SFML/Graphics.hpp>

namespace snake::state{

    //====================================================
    //     Menu
    //====================================================
    /**
     * @brief Class used to create the main menu.
     * 
     */
    class Menu: public State{

        //====================================================
        //     Public
        //====================================================
        public:

            // Constructors
            Menu( window::GameWindow* game_window );

            // Methods
            void drawState() const override;

        //====================================================
        //     Private
        //====================================================
        private:

            // Methods
            void drawLogo() const;
            void drawWidgets() const override;

            // Variables
            window::GameWindow* game_window;
    };
}

#endif