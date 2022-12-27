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
        drawLogo();

        // Drawing widgets
        drawWidgets();

        // Display the state
        this -> game_window -> display();
    }

    //====================================================
    //     drawLogo
    //====================================================
    /**
     * @brief Method used to draw the image logo.
     * 
     */
    void MenuState::drawLogo() const {

        // Creating the texture
        if( ! menu_texture.loadFromFile( "img/logo.png" ) ){
            this -> game_window -> close();
        }

        // Creating the sprite
        sf::Sprite logo_sprite;
        logo_sprite.setTexture( menu_texture, true );
        logo_sprite.setPosition( sf::Vector2f( 290.f, 120.f ) );

        // Drawing the image
        this -> game_window -> draw( logo_sprite );
    }

    //====================================================
    //     drawWidgets
    //====================================================
    /**
     * @brief Method used to draw widgets.
     * 
     */
    void MenuState::drawWidgets() const {

        // Common button settings
        constexpr float x_pos{ 440.f };
        constexpr float width{ 200.f };
        constexpr float height{ 70.f };
        constexpr int32_t text_size{ 24 };
        const sf::Font font{ this -> font };
        const sf::Color idleColor{ sf::Color::Green };
        const sf::Color hoverColor{ sf::Color::Red };
        const sf::Color activeColor{ sf::Color::Blue };

        // Start game button
        auto game_button{ 
            widget::Button( 
                x_pos, 540.f, width, height, font, "Start Game", 
                idleColor, hoverColor, activeColor ) 
        };
        game_button.setTextSize( text_size );
        auto game_action = [ this ]{
            this -> game_window -> states.insert( { "Game", std::make_unique<state::GameState>( state::GameState( game_window ) ) } );
        };
        game_button.setAction( game_action );
        game_button.pack( game_window );

        // Scores button
        auto scores_button{ 
            widget::Button( 
                x_pos, 620.f, width, height, font, "Scores", 
                idleColor, hoverColor, activeColor ) 
        };
        scores_button.setTextSize( text_size );
        scores_button.pack( this -> game_window );

        // Settings button
        auto settings_button{ 
            widget::Button( 
                x_pos, 700.f, width, height, font, "Settings", 
                idleColor, hoverColor, activeColor ) 
        };
        settings_button.setTextSize( text_size );
        settings_button.pack( this -> game_window );

        // Quit button
        auto quit_button{ 
            widget::Button( 
                x_pos, 780.f, width, height, font, "Quit", 
                idleColor, hoverColor, activeColor ) 
        };
        quit_button.setTextSize( text_size );
        quit_button.setAction( [ this ]{ this -> game_window -> close(); } );
        quit_button.pack( game_window );
    }
}