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

// SFML
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Mouse.hpp>

namespace snake::widget{

    //====================================================
    //     textbox_states
    //====================================================
    /**
     * @brief Enum used to define all the textbox states.
     * 
     */
    enum textbox_states{
        TXBX_IDLE = 0,
        TXBX_HOVER,
        TXBX_ACTIVE
    };

    //====================================================
    //     Textbox
    //====================================================
    /**
     * @brief Class used to create the textbox widget.
     * 
     */
    class Textbox{

        //====================================================
        //     Public
        //====================================================
        public:

            // Constructors
            Textbox( float x, float y, float width, float height, 
                    const sf::Font& font, const std::string& text,
                    const sf::Color& idleColor, const sf::Color& hoverColor );


            // pack (template)
            /**
             * @brief Method used to draw the textbox in the window target.
             * 
             * @param target The target to which the textbox is drawn in.
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
            void setTextColor( const sf::Color& color );
            void setText( std::string text );

            // Getters
            void getText() const;

            // Variables
            bool focus;
            sf::Text text;

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
             * @brief Method used for textbox rendering.
             * 
             * @param target The target to draw textbox.
             */
            template <typename T>
            void render( T* target ) const{
                target -> draw( this -> shape );
                target -> draw( this -> text );
            }

            // Variables
            sf::RectangleShape shape;
            sf::Font font;
            sf::Color idleColor;
            sf::Color hoverColor;
            uint16_t textboxState;
    };
}

#endif