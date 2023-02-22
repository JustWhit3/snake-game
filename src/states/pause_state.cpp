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
#include <states/menu_state.hpp>

// Debug
#ifdef DEBUG_SNAKE_GAME
    #include <ptc/print.hpp>
#endif

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
        if( ! state_texture_5.loadFromFile( "img/title_game_background.jpg" ) ){
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
        const float width{ this -> pause_window_size_y * 0.5f };
        const float height{ width * 0.45f };
        const float x_pos = this -> pause_window_size_x * 0.5f - width * 1.25f;
        const float y_pos = this -> pause_window_size_y * 0.5f;
        constexpr int32_t text_size{ 24 };
        const sf::Font font{ this -> font };
        const sf::Color idleColor{ sf::Color( 102, 204, 0 ) };
        const sf::Color hoverColor{ sf::Color( 255, 102, 102 ) };
        const sf::Color activeColor{ sf::Color::Blue };
        const sf::Color textColor{ sf::Color::Black };

        // Yes button
        this -> yes_button = { 
            std::shared_ptr<widget::Button> ( new widget::Button( 
                x_pos, y_pos, width, height, font, "Yes", 
                idleColor, hoverColor, activeColor ) 
            )
        };
        auto yes_action = [ this ]{
            this -> pause_window -> close();
            this -> pause_window -> back_to_menu = true;
        };
        this -> yes_button -> setAction( yes_action );
        this -> yes_button -> setTextSize( text_size );
        this -> yes_button -> setFocus( true );
        this -> yes_button -> setTextColor( textColor );

        // No button
        this -> no_button = { 
            std::shared_ptr<widget::Button> ( new widget::Button( 
                x_pos + width * 1.5f, y_pos, width, height, font, "No", 
                idleColor, hoverColor, activeColor ) 
            )
        };
        auto no_action = [ this ]{
            this -> pause_window -> close();
        };
        this -> no_button -> setAction( no_action );
        this -> no_button -> setTextSize( text_size ); 
        this -> no_button -> setTextColor( textColor );

        // Main text
        this -> text.setFillColor( sf::Color::Black );
        this -> text.setPosition(
           ( this -> pause_window_size_x / 2 - text.getGlobalBounds().width ) * 0.6f, 
           ( this -> pause_window_size_y / 2 - text.getGlobalBounds().height ) * 0.4f
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
        this -> pause_window -> draw( text );
    }
}