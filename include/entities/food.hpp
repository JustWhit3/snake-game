//====================================================
//     File data
//====================================================
/**
 * @file food.hpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2022-12-29
 * @copyright Copyright (c) 2022 Gianluca Bianco under the MIT license.
 */

//====================================================
//     Headers
//====================================================

// Windows
#include <windows/game_window.hpp>

// Entities
#include <entities/entity.hpp>

//====================================================
//     Preprocessor directives
//====================================================
#pragma once
#ifndef SNAKE_GAME_FOOD_ENTITY
#define SNAKE_GAME_FOOD_ENTITY

namespace snake::entity{

    //====================================================
    //     Body
    //====================================================
    /**
     * @brief Class used to construct the snake entity.
     * 
     */
    class Food: public Entity{

        //====================================================
        //     Public
        //====================================================
        public:

            // Constructors
            Food( window::GameWindow* game_window  );

            // Methods
            void draw() const override;

        //====================================================
        //     private
        //====================================================
        private:

            // Variables
            sf::CircleShape food;

            // Constants
            const sf::VideoMode desktop{ sf::VideoMode::getDesktopMode() };
            const sf::VideoMode mode{ sf::VideoMode( 
                    this -> desktop.height, this -> desktop.height, this -> desktop.bitsPerPixel )
                };
            int bound{ static_cast<int>( mode.height - mode.height / 10 ) };
    };
}

#endif