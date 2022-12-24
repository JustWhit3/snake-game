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
    template <class T>
    class State{

        // Protected part
        protected:

            // Constructors
            State(){
                font.loadFromFile( "fonts/source-sans-pro/SourceSansPro-Semibold.otf" );
            }

            // Methods
            virtual void drawWidgets( T* target ) const = 0;

            // Variables
            sf::Font font;
    };
}

#endif