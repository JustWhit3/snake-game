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
    class Entity: public sf::RectangleShape{

        //====================================================
        //     Public
        //====================================================
        public:

            // Methods
    };
}

#endif