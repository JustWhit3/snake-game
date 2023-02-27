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

// Widgets
#include <widgets/widget.hpp>

// SFML
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>

// STL
#include <string>
#include <functional>
#include <stdint.h>

namespace snake::widget{

    //====================================================
    //     Button
    //====================================================
    /**
     * @brief Class used to create the button widget.
     * 
     */
    class Button: public Widget{

        //====================================================
        //     Public
        //====================================================
        public:

            // Constructors
            Button( float x, float y, float width, float height, 
                    const sf::Font& font, const std::string& text, 
                    const sf::Color& idleColor, const sf::Color& hoverColor, const sf::Color& activeColor );

            // Methods
            void setAction( const std::function<void()>& action );
            void setFocus( const bool focus );

        //====================================================
        //     Private
        //====================================================
        private:

            // Methods
            void update( const sf::Vector2f mousePos ) override;

            // Variables
            std::function<void()> action;
            std::function<void()> command_action;
    };       
}

#endif