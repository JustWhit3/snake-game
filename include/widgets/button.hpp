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
#include <windows/game_window.hpp>
#include <windows/pause_window.hpp>

// SFML
#include <SFML/Graphics.hpp>

// STL
#include <string>
#include <functional>

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

            // pack (template)
            /**
             * @brief Method used to draw the button in the GameWindow target.
             * 
             * @param target The target to which the button is drawn in.
             */
            template <typename T>
            void pack( T* target ){
                this -> centering();
                this -> update( target -> mapPixelToCoords( sf::Mouse::getPosition( *target ) ) );
                this -> render( target );
            }
            
            // Setters
            void setTextSize( int32_t size );
            void setOutlineColor( const sf::Color& color );
            void setOutlineThickness( float thickness );
            void setFocus( const bool focus );
            void setTextColor( const sf::Color& color );

            // Variables
            bool focus;

        //====================================================
        //     Private
        //====================================================
        private:

            // Methods
            void update( const sf::Vector2f mousePos );
            constexpr bool isPressed() const;
            void centering();

            // render (template)
            /**
             * @brief Method used for button rendering.
             * 
             * @param target The target to draw button.
             */
            template <typename T>
            void render( T* target ) const{
                target -> draw( this -> shape );
                target -> draw( this -> text );
            }

            // Variables
            sf::RectangleShape shape;
            sf::Font font;
            sf::Text text;
            sf::Color idleColor;
            sf::Color hoverColor;
            sf::Color activeColor;
            std::function<void()> action;
            std::function<void()> command_action;
            uint16_t buttonState;
    };       
}

#endif