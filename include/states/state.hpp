//====================================================
//     File data
//====================================================
/**
 * @file state.hpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2022-12-23
 * @copyright Copyright (c) 2022 Gianluca Bianco under the MIT license.
 */

//====================================================
//     Preprocessor directives
//====================================================
#pragma once
#ifndef SNAKE_GAME_DEFAULT_STATE
#define SNAKE_GAME_DEFAULT_STATE

//====================================================
//     Headers
//====================================================

// SFML
#include <SFML/Graphics.hpp>

namespace snake::state{

    //====================================================
    //     State
    //====================================================
    /**
     * @brief Class used to define base state for the other states.
     * 
     * @tparam T Type of the target to which the state is drawn into.
     */
    class State{

        //====================================================
        //     Public
        //====================================================
        public:

            virtual ~State();

            // Methods
            virtual void drawState() const = 0;
        
        //====================================================
        //     Protected
        //====================================================
        protected:

            // Constructors
            State();


            // Methods
            virtual void drawWidgets() const;

            // Variables
            sf::Font font;
            sf::Color background_color{ sf::Color::White };

            // Static variables
            static sf::Texture menu_texture;
    };
}

#endif