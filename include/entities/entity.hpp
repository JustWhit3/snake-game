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

// Windows
#include <windows/game_window.hpp>

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

            // Methods
            virtual void update();
            virtual void draw() const = 0;
        
        //====================================================
        //     Protected
        //====================================================
        protected:

            // Constructors
            Entity( window::GameWindow* game_window );        
            
            // Variables
            window::GameWindow* game_window;
    };
}

#endif