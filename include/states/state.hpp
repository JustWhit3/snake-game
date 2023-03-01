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
     */
    class State{

        //====================================================
        //     Public
        //====================================================
        public:

            // Constructors
            State();

            // Methods
            virtual void drawState() = 0;
        
        //====================================================
        //     Protected
        //====================================================
        protected:

            // Destructor
            virtual ~State();

            // Methods
            virtual void drawWidgets() = 0;
            virtual void setWidgetsKeys() const;
            virtual void packWidgets() = 0;

            // Variables
            sf::Font font;

            // Static variables
            static sf::Texture state_texture_1;
            static sf::Texture state_texture_2;
            static sf::Texture state_texture_3;
            static sf::Texture state_texture_4;
            static sf::Texture state_texture_5;
            static sf::Texture state_texture_6;
            static sf::Texture state_texture_7;

            // Constants
            sf::Color background_color{ sf::Color::White };
            static constexpr uint16_t waiting_time{ 100 };
    };
}

#endif