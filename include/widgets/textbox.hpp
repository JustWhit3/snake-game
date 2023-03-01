//====================================================
//     File data
//====================================================
/**
 * @file textbox.hpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2022-12-26
 * @copyright Copyright (c) 2022 Gianluca Bianco under the MIT license.
 */

//====================================================
//     Preprocessor directives
//====================================================
#pragma once
#ifndef SNAKE_GAME_textbox_WIDGET
#define SNAKE_GAME_textbox_WIDGET

//====================================================
//     Headers
//====================================================

// Widgets
#include <widgets/widget.hpp>

// SFML
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/String.hpp>
#include <SFML/System/Vector2.hpp>

// STD
#include <string>

//====================================================
//     Required by IWYU
//====================================================
namespace sf{
    class Color;
    class Event;
    class Font;
}

namespace snake::widget{

    //====================================================
    //     Textbox
    //====================================================
    /**
     * @brief Class used to create the textbox widget.
     * 
     */
    class Textbox: public Widget{

        //====================================================
        //     Public
        //====================================================
        public:

            // Constructors
            Textbox( float x, float y, float width, float height, 
                    const sf::Font& font, const std::string& text,
                    const sf::Color& idleColor, const sf::Color& hoverColor, const sf::Color& activeColor );

            // Methods
            void updateText( const sf::Event& event );

            // Getters
            void getText() const;

            // Variables
            std::string saved_text;
            sf::Clock deltaClock;

        //====================================================
        //     Private
        //====================================================
        private:

            // Methods
            void update( const sf::Vector2f mousePos ) override;

            // Variables
            sf::Text input_text;
            sf::String input;
            std::string current_text;
            bool has_been_pressed;
    };
}

#endif