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

// Utility
#include <utility/gui.hpp>

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
            Food( window::GameWindow* game_window );

            // Methods
            void draw() const override;
            void respawn();

            // Variables
            sf::Sprite food;

        //====================================================
        //     private
        //====================================================
        private:

            // Constants
            const int y_bound{ static_cast<int>( utility::getDesktopMode().height - utility::getDesktopMode().height / 10 ) };
            const int x_bound{ static_cast<int>( utility::getDesktopMode().width - utility::getDesktopMode().width / 10 ) };
    };
}

#endif