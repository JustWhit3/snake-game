//====================================================
//     File data
//====================================================
/**
 * @file pause_state.cpp
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

// Windows
#include <windows/pause_window.hpp>

// States
#include <states/state.hpp>
#include <states/pause_state.hpp>

// Widgets
#include <widgets/button.hpp>

// Debug
#ifdef DEBUG_SNAKE_GAME
    #include <ptc/print.hpp>
#endif

// SFML
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Sleep.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp>

// STD
#include <memory>

namespace snake::state{

    //====================================================
    //     Pause (constructor)
    //====================================================
    /**
     * @brief Constructor of the Pause class.
     * 
     * @param pause_window The window to which the state stuff is constructed.
     */
    PauseState::PauseState( window::PauseWindow* pause_window ): 
        pause_window( pause_window ){

        // Draw widgets
        this -> drawWidgets();
    }

    //====================================================
    //     drawState
    //====================================================
    /**
     * @brief Method used to draw the current state.
     * 
     */
    void PauseState::drawState() {

        // Clear the window
        this -> pause_window -> clear( this -> background_color );

        // Drawing images
        this -> drawImg();

        // Drawing widgets
        this -> setWidgetsKeys();
        this -> packWidgets();

        // Display the state
        this -> pause_window -> display();
    }

    //====================================================
    //     drawImg
    //====================================================
    /**
     * @brief Method used to draw the images.
     * 
     */
    void PauseState::drawImg() const {

        // Loading files from textures
        if( ! state_texture_5.loadFromFile( "img/images/title_game_background.jpg" ) ){
            this -> pause_window -> close();
        }

        // Background
        sf::RectangleShape background( sf::Vector2f( this -> pause_window_size_x, this -> pause_window_size_y ) );
        background.setTexture( &state_texture_5, true );

        // Drawing the images
        this -> pause_window -> draw( background );
    }

    //====================================================
    //     drawWidgets
    //====================================================
    /**
     * @brief Method used to draw widgets in the current state.
     * 
     */
    void PauseState::drawWidgets() {

        // Constants
        this -> width = this -> pause_window_size_y * 0.5f;
        this -> height = this -> width * 0.45f;
        this -> x_pos = this -> pause_window_size_x * 0.5f - this -> width * 1.25f;
        this -> y_pos = this -> pause_window_size_y * 0.5f;
        this -> idleColor = sf::Color( 102, 204, 0 );
        this -> hoverColor = sf::Color( 255, 102, 102 );
        this -> activeColor = sf::Color( 102, 102, 255 );

        // Yes button
        this -> yes_button = { 
            std::shared_ptr<widget::Button> ( new widget::Button( 
                    this -> x_pos, 
                    this -> y_pos, 
                    this -> width, 
                    this -> height, 
                    this -> font, 
                    "Yes", 
                    this -> idleColor, 
                    this -> hoverColor, 
                    this -> activeColor 
                ) 
            )
        };
        auto yes_action = [ this ]{
            this -> pause_window -> close();
            this -> pause_window -> back_to_menu = true;
        };
        this -> yes_button -> setAction( yes_action );
        this -> yes_button -> setTextSize( this -> text_size );
        this -> yes_button -> setFocus( true );
        this -> yes_button -> setTextColor( this -> textColor );

        // No button
        this -> no_button = { 
            std::shared_ptr<widget::Button> ( new widget::Button( 
                    this -> x_pos + this -> width * 1.5f, 
                    this -> y_pos, 
                    this -> width, 
                    this -> height, 
                    this -> font, 
                    "No", 
                    this -> idleColor, 
                    this -> hoverColor, 
                    this -> activeColor ) 
            )
        };
        auto no_action = [ this ]{
            this -> pause_window -> close();
        };
        this -> no_button -> setAction( no_action );
        this -> no_button -> setTextSize( this -> text_size ); 
        this -> no_button -> setTextColor( this -> textColor );

        // Main text
        this -> text.setFillColor( sf::Color::Black );
        this -> text.setPosition(
           ( this -> pause_window_size_x / 2 - this -> text.getGlobalBounds().width ) * 0.6f, 
           ( this -> pause_window_size_y / 2 - this -> text.getGlobalBounds().height ) * 0.4f
        );
    }

    //====================================================
    //     setWidgetsKeys
    //====================================================
    /**
     * @brief Method used to set widgets in the current state.
     * 
     */
    void PauseState::setWidgetsKeys() const {
        if( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) && this -> yes_button -> focus ){
            yes_button -> setFocus( false );
            no_button -> setFocus( true );
            sf::sleep( ( sf::milliseconds( this -> waiting_time ) ) );
        }
        else if( sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) && this -> no_button -> focus ){
            this -> yes_button -> setFocus( true );
            this -> no_button -> setFocus( false );
            sf::sleep( ( sf::milliseconds( this -> waiting_time ) ) );
        }
    }

    //====================================================
    //     packWidgets
    //====================================================
    /**
     * @brief Method used to pack widgets in the current state.
     * 
     */
    void PauseState::packWidgets(){

        // Text settings
        this -> text.setFont( this -> font );
        this -> text.setString( "Quit the game?" );

        // Draw stuff
        this -> yes_button -> pack( this -> pause_window );
        this -> no_button -> pack( this -> pause_window );
        this -> pause_window -> draw( this -> text );
    }
}