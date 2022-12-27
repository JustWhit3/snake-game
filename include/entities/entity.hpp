//====================================================
//     File data
//====================================================
/**
 * @file entity.hpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2022-12-27
 * @copyright Copyright (c) 2022 Gianluca Bianco under the MIT license.
 */

//====================================================
//     Preprocessor directives
//====================================================
#pragma once
#ifndef SNAKE_GAME_BASE_ENTITY
#define SNAKE_GAME_BASE_ENTITY

//====================================================
//     Headers
//====================================================

// SFML
#include <SFML/Graphics.hpp>

namespace snake::entity{

    //====================================================
    //     Snake
    //====================================================
    /**
     * @brief Class used to construct the base entity.
     * 
     */
    class Entity{

        //====================================================
        //     Public
        //====================================================
        public:

            // Variables
            float speedV = 0.1f;

        //====================================================
        //     Protected
        //====================================================
        protected:

            // Methods
            virtual void moveSmoothly( const float dir_x, const float dir_y ) = 0;
            virtual void update() = 0;

            // Variables
            float direction_x;
            float direction_y;
    };
}

#endif