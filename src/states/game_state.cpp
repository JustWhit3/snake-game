//====================================================
//     File data
//====================================================
/**
 * @file game_state.cpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2022-12-25
 * @copyright Copyright (c) 2022 Gianluca Bianco under the MIT license.
 */

//====================================================
//     Headers
//====================================================

// Windows
#include <windows/game_window.hpp>

// States
#include <states/game_state.hpp>

// Entities
#include <entities/snake.hpp>
#include <entities/food.hpp>

namespace snake::state{

    //====================================================
    //     Game (constructor)
    //====================================================
    /**
     * @brief Main constructor of the Game class.
     * 
     * @param game_window The window to which the state is drawn.
     */
    GameState::GameState( window::GameWindow* game_window ): 
        game_window( game_window ){
            
        // Default move up
        this -> snake.moveSmoothly( 0.f, - this -> snake.speedV );
    }

    //====================================================
    //     drawState
    //====================================================
    /**
     * @brief Method used to draw the current state.
     * 
     */
    void GameState::drawState() {

        // Clear the window
        this -> game_window -> clear( this -> background_color );

        // Drawing entities
        drawEntities();

        // Display the state
        this -> game_window -> display();
    }

    //====================================================
    //     drawEntities
    //====================================================
    /**
     * @brief Method used to draw the state entities.
     * 
     */
    void GameState::drawEntities() {

        // Drawing the snake body entity
        this -> snake.update();   
        snake.draw( this -> game_window );
        food.draw( this -> game_window );
    }
}