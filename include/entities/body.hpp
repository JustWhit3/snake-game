//====================================================
//     File data
//====================================================
/**
 * @file body.hpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2022-12-27
 * @copyright Copyright (c) 2022 Gianluca Bianco under the MIT license.
 */

//====================================================
//     Preprocessor directives
//====================================================
#pragma once
#ifndef SNAKE_GAME_BODY_ENTITY
#define SNAKE_GAME_BODY_ENTITY

//====================================================
//     Headers
//====================================================

// Entities
#include <entities/entity.hpp>

// SFML
#include <SFML/Graphics.hpp>

namespace snake::entity{

    //====================================================
    //     Body
    //====================================================
    /**
     * @brief Class used to construct the snake entity.
     * 
     */
    class Body: public Entity, public sf::RectangleShape{

        //====================================================
        //     Public
        //====================================================
        public:

            // Constructors
            Body();

            // Methods
            void update() override;
            void moveSmoothly( const float dir_x, const float dir_y ) override;
    };
}

#endif