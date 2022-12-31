//====================================================
//     File data
//====================================================
/**
 * @file loose_state.hpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2022-12-31
 * @copyright Copyright (c) 2022 Gianluca Bianco under the MIT license.
 */

//====================================================
//     Preprocessor directives
//====================================================
#pragma once
#ifndef SNAKE_GAME_GAME_OVER_STATE
#define SNAKE_GAME_GAME_OVER_STATE

//====================================================
//     Headers
//====================================================

// Windows
#include <windows/game_window.hpp>

// States
#include <states/state.hpp>

namespace snake::state{

    class LooseState: public State{

        //====================================================
        //     Public
        //====================================================
        public:

            // Constructors
            LooseState( window::GameWindow* game_window );

            // Methods
            void drawState() override;

        //====================================================
        //     Private
        //====================================================
        private:

            // Methods
            void drawWidgets() override;
            void setWidgetsKeys() const override;
            void packWidgets() override;

            // Variables
            window::GameWindow* game_window;
            sf::RectangleShape state_dimension;

            // Widgets here...
    };
}

#endif