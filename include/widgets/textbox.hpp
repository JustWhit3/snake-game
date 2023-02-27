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
#include <SFML/Window/Event.hpp>
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
        TXBX_ACTIVE,
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
                    const sf::Color& idleColor, const sf::Color& hoverColor, const sf::Color& activeColor );


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

            // Methods
            void updateText( const sf::Event& event );

            // Setters
            void setTextSize( int32_t size );
            void setOutlineColor( const sf::Color& color );
            void setOutlineThickness( float thickness );
            void setTextColor( const sf::Color& color );
            void setText( std::string text );

            // Getters
            void getText() const;

            // Variables
            sf::RectangleShape shape;
            bool focus;
            sf::Text text;
            std::string saved_text;

        //====================================================
        //     Private
        //====================================================
        private:

            // Methods
            void update( const sf::Vector2f mousePos );
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
            sf::Font font;
            sf::Color idleColor;
            sf::Color hoverColor;
            sf::Color activeColor;
            uint16_t textboxState;
            sf::Text input_text;
            sf::String input;
            std::string current_text;
            bool has_been_pressed;
    };
}

#endif