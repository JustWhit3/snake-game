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
#include <SFML/Graphics/Color.hpp> 
#include <SFML/Graphics/Font.hpp>

// STD
#include <cstdint>

// Required by IWYU
namespace sf { 
    class Texture; 
}

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

            // Constructors
            State();

            // Destructor
            virtual ~State();

            // Methods
            virtual void drawState() = 0;
        
        //====================================================
        //     Protected
        //====================================================
        protected:

            // Methods
            virtual void drawWidgets();
            virtual void setWidgetsKeys() const;
            virtual void packWidgets();

            // Variables
            sf::Font font;

            // Static variables
            static sf::Texture state_texture;

            // Constants
            sf::Color background_color{ sf::Color::White };
            static constexpr uint16_t waiting_time{ 230 };
    };
}

#endif