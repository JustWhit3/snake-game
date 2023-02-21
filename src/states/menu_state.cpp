//====================================================
//     File data
//====================================================
/**
 * @file menu_state.cpp
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
#include <windows/game_window.hpp>

// States
#include "states/state.hpp"
#include <states/menu_state.hpp>
#include <states/game_state.hpp>

// Widgets
#include <widgets/button.hpp>

// SFML
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Sleep.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Keyboard.hpp>

// Debug
#ifdef DEBUG_SNAKE_GAME
    #include <ptc/print.hpp>
#endif

// STD
#include <memory>
#include <cstdint>
#include <map>
#include <string_view>

namespace snake::state{

    //====================================================
    //     Menu (constructor)
    //====================================================
    /**
     * @brief Constructor of the Menu class.
     * 
     * @param game_window The window to which the state stuff is constructed.
     */
    MenuState::MenuState( window::GameWindow* game_window ): 
        game_window( game_window ){

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
    void MenuState::drawState() {

        // Clear the window
        this -> game_window -> clear( this -> background_color );

        // Drawing images
        this -> drawImg();

        // Drawing widgets
        this -> setWidgetsKeys();
        this -> packWidgets();

        // Display the state
        this -> game_window -> display();
    }

    //====================================================
    //     drawImg
    //====================================================
    /**
     * @brief Method used to draw the image logo.
     * 
     */
    void MenuState::drawImg() const {

        // Loading files from textures
        if( ! state_texture_1.loadFromFile( "img/logo_small.png" ) ){
            this -> game_window -> close();
        }
        if( ! state_texture_2.loadFromFile( "img/snake_branch.png" ) ){
            this -> game_window -> close();
        }
        if( ! state_texture_3.loadFromFile( "img/menu_background.jpg" ) ){
            this -> game_window -> close();
        }

        // Logo
        sf::Sprite logo_sprite( state_texture_1 );
        logo_sprite.setPosition( 
           ( this -> game_window_size_x - logo_sprite.getGlobalBounds().width ) * 0.5f, 
           ( this -> game_window_size_y - logo_sprite.getGlobalBounds().height ) * 0.2f
        );

        // Snake on the branch
        sf::Sprite snake_branch_sprite( state_texture_2 );
        snake_branch_sprite.setPosition( 
           0, 
           ( this -> game_window_size_y - snake_branch_sprite.getGlobalBounds().height ) * 0.25f
        );

        // Background
        sf::RectangleShape background( sf::Vector2f( this -> game_window_size_x, this -> game_window_size_y ) );
        background.setTexture( &state_texture_3, true );

        // Drawing the images
        this -> game_window -> draw( background );
        this -> game_window -> draw( snake_branch_sprite );
        this -> game_window -> draw( logo_sprite );
    }

    //====================================================
    //     drawWidgets
    //====================================================
    /**
     * @brief Method used to draw widgets in the current state.
     * 
     */
    void MenuState::drawWidgets() {
        
        // Constants
        const float width{ this -> game_window_size_y * 0.2f };
        const float height{ width * 0.35f };
        const float x_pos = ( this -> game_window_size_x * 0.5f - width * 0.5f );
        constexpr int32_t text_size{ 24 };
        const sf::Font font{ this -> font };
        const sf::Color idleColor{ sf::Color( 102, 204, 0 ) };
        const sf::Color hoverColor{ sf::Color( 255, 102, 102 ) };
        const sf::Color activeColor{ sf::Color::Blue };
        const sf::Color textColor{ sf::Color::Black };

        // Game button
        this -> game_button = { 
            std::shared_ptr<widget::Button> ( new widget::Button( 
                x_pos, this -> game_window_size_y * 0.5f - height * 0.5f + 80.f, width, height, font, "Start Game", 
                idleColor, hoverColor, activeColor ) 
            )
        };
        auto game_action = [ this ]{
            this -> game_window -> states.insert( 
                { "Game", std::make_shared<state::GameState>( state::GameState( game_window ) ) } 
            );
        };
        this -> game_button -> setAction( game_action );
        this -> game_button -> setTextSize( text_size );
        this -> game_button -> setFocus( true );
        this -> game_button -> setTextColor( textColor );

        // Scores button
        this -> scores_button = { 
            std::shared_ptr<widget::Button> ( new widget::Button( 
                x_pos, this -> game_window_size_y * 0.5f - height * 0.5f + 160.f, width, height, font, "Scores", 
                idleColor, hoverColor, activeColor ) 
            )
        };
        this -> scores_button -> setTextSize( text_size ); 
        this -> scores_button -> setTextColor( textColor );
        
        // Settings button
        this -> settings_button = { 
            std::shared_ptr<widget::Button> ( new widget::Button( 
                x_pos, this -> game_window_size_y * 0.5f - height * 0.5f + 240.f, width, height, font, "Settings", 
                idleColor, hoverColor, activeColor ) 
            )
        };
        this -> settings_button -> setTextSize( text_size );
        this -> settings_button -> setTextColor( textColor );

        // Quit button
        this -> quit_button = { 
            std::shared_ptr<widget::Button> ( new widget::Button( 
                x_pos, this -> game_window_size_y * 0.5f - height * 0.5f + 320.f, width, height, font, "Quit", 
                idleColor, hoverColor, activeColor ) 
            )
        };
        this -> quit_button -> setAction( [ this ]{ this -> game_window -> close(); } );
        this -> quit_button -> setTextSize( text_size );
        this -> quit_button -> setTextColor( textColor );
    }

    //====================================================
    //     setWidgets
    //====================================================
    /**
     * @brief Method used to set widgets in the current state.
     * 
     */
    void MenuState::setWidgetsKeys() const {

        // Map game button to scores button
        if( sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) && game_button -> focus ){
            game_button -> setFocus( false );
            scores_button -> setFocus( true );
            sf::sleep( ( sf::milliseconds( this -> waiting_time ) ) );
        }
        else if( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) && scores_button -> focus ){
            game_button -> setFocus( true );
            scores_button -> setFocus( false );
            sf::sleep( ( sf::milliseconds( this -> waiting_time ) ) );
        }

        // Map scores button to settings button
        if( sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) && scores_button -> focus ){
            scores_button -> setFocus( false );
            settings_button -> setFocus( true );
            sf::sleep( ( sf::milliseconds( this -> waiting_time ) ) );
        }
        else if( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) && settings_button -> focus ){
            scores_button -> setFocus( true );
            settings_button -> setFocus( false );
            sf::sleep( ( sf::milliseconds( this -> waiting_time ) ) );
        }

        // Map settings button to quit button
        if( sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) && settings_button -> focus ){
            settings_button -> setFocus( false );
            quit_button -> setFocus( true );
            sf::sleep( ( sf::milliseconds( this -> waiting_time ) ) );
        }
        else if( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) && quit_button -> focus ){
            settings_button -> setFocus( true );
            quit_button -> setFocus( false );
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
    void MenuState::packWidgets(){
        this -> game_button -> pack( this -> game_window );
        this -> scores_button -> pack( this -> game_window );
        this -> settings_button -> pack( this -> game_window );
        this -> quit_button -> pack( this -> game_window );
    }
}