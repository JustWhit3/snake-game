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
#include <SFML/System/Vector2.hpp>

// STL
#include <string>
#include <functional>

//====================================================
//     Required by IWYU
//====================================================
namespace sf{
    class Color;
    class Font;
}

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