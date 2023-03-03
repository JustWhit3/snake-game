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
#include <states/state.hpp>
#include <states/menu_state.hpp>
#include <states/game_state.hpp>
#include <states/options_state.hpp>
#include <states/scores_state.hpp>

// Widgets
#include <widgets/button.hpp>

// SFML
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Sleep.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Audio.hpp>

// Debug
#ifdef DEBUG_SNAKE_GAME
    #include <ptc/print.hpp>
#endif

// STD
#include <memory>
#include <cstdint>
#include <string_view>
#include <unordered_map>

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
     * @brief Method used to draw the images.
     * 
     */
    void MenuState::drawImg(){

        // Loading files from textures
        if( ! this -> state_texture_1.loadFromFile( "img/images/logo.png" ) ){
            this -> game_window -> close();
        }
        if( ! this -> state_texture_2.loadFromFile( "img/images/snake_branch.png" ) ){
            this -> game_window -> close();
        }
        if( ! this -> state_texture_3.loadFromFile( "img/images/menu_background.jpg" ) ){
            this -> game_window -> close();
        }

        // Logo
        this ->logo_sprite.setTexture( this -> state_texture_1 );
        this -> logo_sprite.setPosition( 
           ( this -> game_window_size_x - this -> logo_sprite.getGlobalBounds().width ) * 0.5f, 
           ( this -> game_window_size_y - this -> logo_sprite.getGlobalBounds().height ) * 0.2f
        );

        // Snake on the branch
        this -> snake_branch_sprite.setTexture( this -> state_texture_2 );
        this -> snake_branch_sprite.setPosition( 
           0, 
           ( this -> game_window_size_y - this -> snake_branch_sprite.getGlobalBounds().height ) * 0.25f
        );

        // Background
        this -> background.setSize( sf::Vector2f( this -> game_window_size_x, this -> game_window_size_y ) );
        this -> background.setTexture( &this -> state_texture_3, true );

        // Drawing the images
        this -> game_window -> draw( this -> background );
        this -> game_window -> draw( this -> snake_branch_sprite );
        this -> game_window -> draw( this -> logo_sprite );
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
        this -> width = this -> game_window_size_y * 0.2f;
        this -> height = this -> width * 0.35f;
        this -> x_pos = ( this -> game_window_size_x * 0.5f - this -> width * 0.5f );
        this -> idleColor = sf::Color( 102, 204, 0 );
        this -> hoverColor = sf::Color( 255, 102, 102 );
        this -> activeColor = sf::Color( 102, 102, 255 );

        // Game button
        this -> game_button = { 
            std::shared_ptr<widget::Button> ( new widget::Button( 
                    this -> x_pos, 
                    this -> game_window_size_y * 0.5f - this -> height * 0.5f + 80.f, 
                    this -> width, 
                    this -> height, 
                    this -> font, 
                    "Start Game", 
                    this -> idleColor, 
                    this -> hoverColor, 
                    this -> activeColor
                ) 
            )
        };
        auto game_action = [ this ]{
            this -> game_window -> game_window_states.insert( 
                { "Game", std::make_shared<state::GameState>( state::GameState( this -> game_window ) ) } 
            );
        };
        this -> game_button -> setAction( game_action );
        this -> game_button -> setTextSize( this -> text_size );
        this -> game_button -> setFocus( true );
        this -> game_button -> setTextColor( this -> textColor );

        // Scores button
        this -> scores_button = { 
            std::shared_ptr<widget::Button> ( new widget::Button( 
                    this -> x_pos, 
                    this -> game_window_size_y * 0.5f - this -> height * 0.5f + 160.f, 
                    this -> width, 
                    this -> height, 
                    this -> font, 
                    "Scores", 
                    this -> idleColor, 
                    this -> hoverColor, 
                    this -> activeColor 
                ) 
            )
        };
        auto scores_action = [ this ]{
            this -> game_window -> game_window_states.insert( 
                { "Scores", std::make_shared<state::ScoresState>( state::ScoresState( this -> game_window ) ) } 
            );
        };
        this -> scores_button -> setAction( scores_action );
        this -> scores_button -> setTextSize( this -> text_size ); 
        this -> scores_button -> setTextColor( this -> textColor );
        
        // Settings button
        this -> settings_button = { 
            std::shared_ptr<widget::Button> ( new widget::Button( 
                    this -> x_pos, 
                    this -> game_window_size_y * 0.5f - this -> height * 0.5f + 240.f, 
                    this -> width, 
                    this -> height, 
                    this -> font, 
                    "Settings", 
                    this -> idleColor, 
                    this -> hoverColor, 
                    this -> activeColor 
                ) 
            )
        };
        auto settings_action = [ this ]{
            this -> game_window -> game_window_states.insert( 
                { "Options", std::make_shared<state::OptionsState>( state::OptionsState( this -> game_window ) ) } 
            );
        };
        this -> settings_button -> setAction( settings_action );
        this -> settings_button -> setTextSize( this -> text_size );
        this -> settings_button -> setTextColor( this -> textColor );

        // Quit button
        this -> quit_button = { 
            std::shared_ptr<widget::Button> ( new widget::Button( 
                    this -> x_pos, 
                    this -> game_window_size_y * 0.5f - this -> height * 0.5f + 320.f, 
                    this -> width, 
                    this -> height, 
                    this -> font, 
                    "Quit", 
                    this -> idleColor, 
                    this -> hoverColor, 
                    this -> activeColor 
                ) 
            )
        };
        this -> quit_button -> setAction( [ this ]{ this -> game_window -> close(); } );
        this -> quit_button -> setTextSize( this -> text_size );
        this -> quit_button -> setTextColor( this -> textColor );

        // Version number text
        this -> metadata.setFillColor( this -> textColor );
        this -> metadata.setPosition( 
            game_window_size_x * 0.03f, 
            game_window_size_y * 0.90f 
        );
        this -> metadata.setCharacterSize( this -> text_size + 6 );
    }

    //====================================================
    //     setWidgetsKeys
    //====================================================
    /**
     * @brief Method used to set widgets in the current state.
     * 
     */
    void MenuState::setWidgetsKeys() const {

        // Map game button to scores button
        if( sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) && this -> game_button -> focus ){
            this -> game_button -> setFocus( false );
            this -> scores_button -> setFocus( true );
            sf::sleep( ( sf::milliseconds( this -> waiting_time ) ) );
        }
        else if( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) && this -> scores_button -> focus ){
            this -> game_button -> setFocus( true );
            this -> scores_button -> setFocus( false );
            sf::sleep( ( sf::milliseconds( this -> waiting_time ) ) );
        }

        // Map scores button to settings button
        if( sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) && this -> scores_button -> focus ){
            this -> scores_button -> setFocus( false );
            this -> settings_button -> setFocus( true );
            sf::sleep( ( sf::milliseconds( this -> waiting_time ) ) );
        }
        else if( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) && this -> settings_button -> focus ){
            this -> scores_button -> setFocus( true );
            this -> settings_button -> setFocus( false );
            sf::sleep( ( sf::milliseconds( this -> waiting_time ) ) );
        }

        // Map settings button to quit button
        if( sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) && this -> settings_button -> focus ){
            this -> settings_button -> setFocus( false );
            this -> quit_button -> setFocus( true );
            sf::sleep( ( sf::milliseconds( this -> waiting_time ) ) );
        }
        else if( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) && this -> quit_button -> focus ){
            this -> settings_button -> setFocus( true );
            this -> quit_button -> setFocus( false );
            sf::sleep( ( sf::milliseconds( this -> waiting_time ) ) );
        }

        // Map game button to quit button
        if( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) && this -> game_button -> focus ){
            this -> game_button -> setFocus( false );
            this -> quit_button -> setFocus( true );
            sf::sleep( ( sf::milliseconds( this -> waiting_time ) ) );
        }
        else if( sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) && this -> quit_button -> focus ){
            this -> game_button -> setFocus( true );
            this -> quit_button -> setFocus( false );
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

        // Version number text
        this -> metadata.setFont( this -> font );
        this -> metadata.setString( "Current version: 0.2.0\nCopyright (c) 2022 Gianluca Bianco under the MIT license" );

        // Draw stuff
        this -> game_button -> pack( this -> game_window );
        this -> scores_button -> pack( this -> game_window );
        this -> settings_button -> pack( this -> game_window );
        this -> quit_button -> pack( this -> game_window );
        this -> game_window -> draw( this -> metadata );
    }
}