//====================================================
//     File data
//====================================================
/**
 * @file snake.hpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2022-12-27
 * @copyright Copyright (c) 2022 Gianluca Bianco under the MIT license.
 */

//====================================================
//     Preprocessor directives
//====================================================
#pragma once
#ifndef SNAKE_GAME_SNAKE_ENTITY
#define SNAKE_GAME_SNAKE_ENTITY

//====================================================
//     Headers
//====================================================

// Windows
#include <windows/game_window.hpp>

// Entities
#include <entities/entity.hpp>

// SFML
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>

// STD
#include <vector>
#include <limits>

namespace snake::entity{

    //====================================================
    //     Body
    //====================================================
    /**
     * @brief Class used to construct the snake entity.
     * 
     */
    class Snake: public Entity{

        //====================================================
        //     Public
        //====================================================
        public:

            // Constructors
            Snake( window::GameWindow* game_window );

            // Methods
            void update();
            void moveSmoothly( const float dir_x, const float dir_y );
            void draw() const override;
            void bodyGrow();
            void relHeadPos( float x, float y );
            void death();
            void setGrowPosition( float x, float y );

            // Variables
            float speedV{ 25.f };
            sf::Sprite head;
            sf::RectangleShape body_shape;
            std::vector<sf::RectangleShape> body;
            
        //====================================================
        //     Private
        //====================================================
        private:

            // Methods
            void rotate( float angle );

            // Variables
            float direction_x;
            float direction_y;

            // Constants
            const uint64_t game_window_size_x = this -> game_window -> getSize().x;
            const float infinitesimal_speedV = std::numeric_limits<float>::epsilon();
            const float body_dimension = 25.0f;
    };
}

#endif