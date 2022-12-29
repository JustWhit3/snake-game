//====================================================
//     File data
//====================================================
/**
 * @file game_state.hpp
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
#include <windows/game_window.hpp>

// States
#include <states/state.hpp>

// Entities
#include <entities/snake.hpp>
#include <entities/food.hpp>

namespace snake::state{

    //====================================================
    //     Game
    //====================================================
    /**
     * @brief Class used to create the game state.
     * 
     */
    class GameState: public State{

        //====================================================
        //     Public
        //====================================================
        public:

            // Constructors
            GameState( window::GameWindow* game_window );

            // Methods
            void drawState() override;

        //====================================================
        //     Private
        //====================================================
        private:

            // Methods
            constexpr void drawEntities() const;
            constexpr void updateEntities() const;

            // Variables
            window::GameWindow* game_window;
            entity::Snake* snake = new entity::Snake( game_window );
            entity::Food* food = new entity::Food( game_window );
    };
}

#endif