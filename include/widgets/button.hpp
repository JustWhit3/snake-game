//====================================================
//     File data
//====================================================
/**
 * @file button.hpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2022-12-23
 * @copyright Copyright (c) 2022 Gianluca Bianco under the MIT license.
 */

//====================================================
//     Preprocessor directives
//====================================================
#pragma once
#ifndef SNAKE_GAME_BUTTON_WIDGET
#define SNAKE_GAME_BUTTON_WIDGET

//====================================================
//     Headers
//====================================================

// Windows
#include <windows/game.hpp>

// SFML
#include <SFML/Graphics.hpp>

// STL
#include <string>

namespace snake::widget{

    //====================================================
    //     button_states
    //====================================================
    /**
     * @brief Enum used to define all the button states.
     * 
     */
    enum button_states{
        BTN_IDLE = 0,
        BTN_HOVER,
        BTN_ACTIVE
    };

    //====================================================
    //     Menu
    //====================================================
    /**
     * @brief Class used to create the button widget.
     * 
     */
    class Button{

        // Public part
        public:

            // Constructors
            Button( 
                float x, float y, float width, float height, 
                sf::Font font, std::string text, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor
            );

            // Functions
            void render( window::GameWindow* target ) const;
            void update( const sf::Vector2f mousePos );
            void pack( window::GameWindow* target );
            constexpr bool isPressed() const;
            void centering();
            
            // Setters
            void setTextSize( int32_t size );
        
        // Private part
        private:

            // Variables
            uint16_t buttonState;
            sf::RectangleShape shape;
            sf::Font font;
            sf::Text text;
            sf::Color idleColor;
            sf::Color hoverColor;
            sf::Color activeColor;
    };
}

#endif