//====================================================
//     File data
//====================================================
/**
 * @file button.cpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2022-12-22
 * @copyright Copyright (c) 2022 Gianluca Bianco under the MIT license.
 */

//====================================================
//     Preprocessor directives
//====================================================

// ptc-print
#ifdef DEBUG_SNAKE_GAME
    #define PTC_ENABLE_PERFORMANCE_IMPROVEMENTS
    #define PTC_DISABLE_STD_TYPES_PRINTING
#endif

//====================================================
//     Headers
//====================================================

// Widgets
#include <widgets/widget.hpp>
#include <widgets/button.hpp>

// SFML
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp> 
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

// Debug
#ifdef DEBUG_SNAKE_GAME
    #include <ptc/print.hpp>
#endif

// STD
#include <functional>
#include <string>

//====================================================
//     Required by IWYU
//====================================================
namespace sf{
    class Font;
}

namespace snake::widget{

    //====================================================
    //     Button (constructor)
    //====================================================
    /**
     * @brief Main constructor of the button class.
     * 
     * @param x X position of the button.
     * @param y Y position of the button.
     * @param width Button width.
     * @param height Button height.
     * @param font Button text font.
     * @param text Button text
     * @param idleColor Default color of the button.
     * @param hoverColor Button color when passing with mouse.
     * @param activeColor Button color when clicking
     */
    Button::Button( float x, float y, float width, float height, 
                    const sf::Font& font, const std::string& text, 
                    const sf::Color& idleColor, const sf::Color& hoverColor, const sf::Color& activeColor ):
        Widget( x, y, width, height, font, text, idleColor, hoverColor, activeColor ),
        action( []{} ),
        command_action( []{} ),
        switch_sound_already_played( false ){

        // Load sounds
        this -> loadSounds();
    }
    
    //====================================================
    //     update
    //====================================================
    /**
     * @brief Method used to update the booleans for hover and pressed.
     * 
     * @param mouse_pos The mouse position.
     */
    void Button::update( const sf::Vector2f mousePos ){

        // Idle
        this -> widgetState = WDGT_IDLE;

        // Extra settings for sound
        if( this -> focus == false ){
            this -> switch_sound_already_played = false;
        }

        // Mouse clicked
        if( this -> shape.getGlobalBounds().contains( mousePos ) ){
            this -> widgetState = WDGT_HOVER;

            if( sf::Mouse::isButtonPressed( sf::Mouse::Left ) ){
                this -> widgetState = WDGT_ACTIVE;
            }
        }

        // Enter clicked
        else if( this -> focus == true ){
            this -> widgetState = WDGT_HOVER;

            if( sf::Keyboard::isKeyPressed( sf::Keyboard::Return ) ){
                this -> widgetState = WDGT_ACTIVE;
            }
        }

        // Switch cases for button states
        switch( this -> widgetState ){
            case WDGT_IDLE:
                this -> shape.setFillColor( this -> idleColor );
                break;

            case WDGT_HOVER:
                this -> shape.setFillColor( this -> hoverColor );

                if( this -> switch_sound_already_played == false ){
                    this -> button_switch_sound.play();
                    this -> switch_sound_already_played = true;
                }
                break;

            case WDGT_ACTIVE:
                this -> shape.setFillColor( this -> activeColor );
                this -> button_click_sound.play();
                this -> action();
                break;

            default:
                this -> shape.setFillColor( sf::Color::Red );
                break;
        }
    }

    //====================================================
    //     setAction
    //====================================================
    /**
     * @brief Function used to set an action which is performed by the button when pressed.
     * 
     * @param action The function which should be ran by the button when pressed.
     */
    void Button::setAction( const std::function<void()>& action ){
        this -> action = action;
    }

    //====================================================
    //     setFocus
    //====================================================
    /**
     * @brief Method used to move focus on the button.
     * 
     * @param focus The focus condition.
     */
    void Button::setFocus( const bool focus ){
        this -> focus = focus;
    }

    //====================================================
    //     loadSounds
    //====================================================
    /**
     * @brief Method used to load widget sounds.
     * 
     */
    void Button::loadSounds(){

        // Button click
        this -> widget_sound_1.loadFromFile( "sounds/effects/button_click.wav" );
        this -> button_click_sound.setBuffer( this -> widget_sound_1 );

        // Button switch
        this -> widget_sound_2.loadFromFile( "sounds/effects/button_switch.wav" );
        this -> button_switch_sound.setBuffer( this -> widget_sound_2 );
    }
}
