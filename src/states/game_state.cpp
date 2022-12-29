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
    //     GameState (constructor)
    //====================================================
    /**
     * @brief Main constructor of the Game class.
     * 
     * @param game_window The window to which the state is drawn.
     */
    GameState::GameState( window::GameWindow* game_window ): 
        game_window( game_window ){

        // Set snake head and texture properties
        this -> snake -> head_texture.loadFromFile( "img/snake_head.png" );
        this -> snake -> head.setTexture( this -> snake -> head_texture );
        this -> snake -> head.rotate( 180 );
        this -> snake -> head.setPosition( 567.5f, 907.f );

        // Default move up
        this -> snake -> moveSmoothly( 0.f, - this -> snake -> speedV );
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
        this -> drawEntities();
        this -> updateEntities();
        
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
    constexpr void GameState::drawEntities() const {
        this -> snake -> draw();
        this -> food -> draw();
    }

    //====================================================
    //     updateEntities
    //====================================================
    /**
     * @brief Method used to update the state entities.
     * 
     */
    constexpr void GameState::updateEntities() const {
        this -> snake -> update(); 
    }
}