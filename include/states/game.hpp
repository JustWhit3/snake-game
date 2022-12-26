//====================================================
//     File data
//====================================================
/**
 * @file game.hpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2022-12-25
 * @copyright Copyright (c) 2022 Gianluca Bianco under the MIT license.
 */

//====================================================
//     Preprocessor directives
//====================================================
#pragma once
#ifndef SNAKE_GAME_GAME_STATE
#define SNAKE_GAME_GAME_STATE

//====================================================
//     Headers
//====================================================

// Windows
#include <windows/game.hpp>

// States
#include <states/state.hpp>

namespace snake::state{

    //====================================================
    //     Game
    //====================================================
    /**
     * @brief Class used to create the game state.
     * 
     */
    class Game: public State{

        //====================================================
        //     Public
        //====================================================
        public:

            // Constructors
            Game( window::GameWindow* game_window );

            // Methods
            void drawState() const override;

        //====================================================
        //     Private
        //====================================================
        private:

            // Variables
            window::GameWindow* game_window;
    };
}

#endif