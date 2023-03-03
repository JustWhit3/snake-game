//====================================================
//     File data
//====================================================
/**
 * @file widget.hpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2022-12-27
 * @copyright Copyright (c) 2022 Gianluca Bianco under the MIT license.
 */

//====================================================
//     Preprocessor directives
//====================================================
#pragma once
#ifndef SNAKE_GAME_DEFAULT_WIDGET
#define SNAKE_GAME_DEFAULT_WIDGET

//====================================================
//     Headers
//====================================================

// SFML
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>
#include <SFML/Audio.hpp>

// STD
#include <cstdint>
#include <string>

namespace snake::widget{

    //====================================================
    //     button_states
    //====================================================
    /**
     * @brief Enum used to define all the button states.
     * 
     */
    enum widget_states{
        WDGT_IDLE = 0,
        WDGT_HOVER,
        WDGT_ACTIVE
    };

    //====================================================
    //     Widget
    //====================================================
    /**
     * @brief Class used to define base widget for the other widgets.
     * 
     */
    class Widget{

        //====================================================
        //     Public
        //====================================================
        public:

            // Setters
            void setTextSize( uint32_t size );
            void setOutlineColor( const sf::Color& color );
            void setOutlineThickness( float thickness );
            void setTextColor( const sf::Color& color );
            void setText( std::string text );

            // pack (template)
            /**
             * @brief Method used to draw the widget in the window target.
             * 
             * @param target The target to which the widget is drawn in.
             */
            template <typename T>
            void pack( T* target ){
                this -> centering();
                this -> update( target -> mapPixelToCoords( sf::Mouse::getPosition( *target ) ) );
                this -> render( target );
            }

            // Variables
            bool focus;
            sf::RectangleShape shape;
            sf::Text text;
        
        //====================================================
        //     Protected
        //====================================================
        protected:

            // Constructors
            Widget( float x, float y, float width, float height, 
                    const sf::Font& font, const std::string& text, 
                    const sf::Color& idleColor, const sf::Color& hoverColor, const sf::Color& activeColor );

            // Methods
            virtual void update( const sf::Vector2f mousePos ) = 0;
            virtual void loadSounds() = 0;
            void centering();

            // render (template)
            /**
             * @brief Method used for widget rendering.
             * 
             * @param target The target to draw widget.
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
            uint16_t widgetState;

            // Static variables
            static sf::SoundBuffer widget_sound_1;
            static sf::SoundBuffer widget_sound_2;
            static sf::SoundBuffer widget_sound_3;
    };
}

#endif