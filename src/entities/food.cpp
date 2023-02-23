//====================================================
//     File data
//====================================================
/**
 * @file food.cpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2022-12-29
 * @copyright Copyright (c) 2022 Gianluca Bianco under the MIT license.
 */

//====================================================
//     Preprocessor directives
//====================================================

// ptc-print
#ifdef DEBUG_SNAKE_GAME
    #define PTC_ENABLE_PERFORMANCE_IMPROVEMENTS
    #define PTC_DISABLE_STD_TYPES_PRINTING
#endif

//====================================================
//     Headers
//====================================================

// Windows
#include <windows/game_window.hpp>

// Entities
#include <entities/entity.hpp>
#include <entities/food.hpp>

// Utility
#include <utility/generic.hpp>

// Debug
#ifdef DEBUG_SNAKE_GAME
    #include <ptc/print.hpp>
#endif

// SFML
#include <SFML/Graphics/Sprite.hpp>

namespace snake::entity{

    //====================================================
    //     Food (constructor)
    //====================================================
    /**
     * @brief Constructor of the food class.
     * 
     */
    Food::Food( window::GameWindow* game_window ): Entity( game_window ){
        
        // Setting random first position
        float x_random = utility::random( 0, this -> x_bound );
        float y_random = utility::random( 80, this -> y_bound );

        // Food settings
        this -> food.setPosition( x_random, y_random );
    }

    //====================================================
    //     draw
    //====================================================
    /**
     * @brief Method used to draw the entity.
     * 
     */
    void Food::draw() const {
        this -> game_window -> draw( this -> food );
    }

    //====================================================
    //     respawn
    //====================================================
    /**
     * @brief Method used to respawn food when there is collision between snake and itself.
     * 
     */
    void Food::respawn(){
        float x_random = utility::random( 0, this -> x_bound );
        float y_random = utility::random( 80, this -> y_bound );
        this -> food.setPosition( x_random, y_random );
    }
}