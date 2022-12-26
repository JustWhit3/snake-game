//====================================================
//     File data
//====================================================
/**
 * @file menu.cpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2022-12-22
 * @copyright Copyright (c) 2022 Gianluca Bianco under the MIT license.
 */

//====================================================
//     Headers
//====================================================

// Windows
#include <windows/game.hpp>

// States
#include <states/menu.hpp>
#include <states/game.hpp>

// Widgets
#include <widgets/button.hpp>

// STD
#include <memory>

namespace snake::state{

    //====================================================
    //     Menu (constructor)
    //====================================================
    /**
     * @brief Constructor of the Menu class.
     * 
     * @param game_window The window to which the state stuff is constructed.
     */
    Menu::Menu( window::GameWindow* game_window ): 
        game_window( game_window ){
    }

    //====================================================
    //     drawState
    //====================================================
    /**
     * @brief Method used to draw the current state.
     * 
     */
    void Menu::drawState() const {

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
    void Menu::drawLogo() const {

        // Creating the texture
        if( ! menu_texture.loadFromFile( "img/logo.png" ) ){
            this -> game_window -> close();
        }

        // Creating the sprite
        sf::Sprite logo_sprite;
        logo_sprite.setTexture( menu_texture, true );
        logo_sprite.setPosition( sf::Vector2f( 280, 120 ) );

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
    void Menu::drawWidgets() const {

        // Common button settings
        constexpr int32_t x_pos{ 440 };
        constexpr int32_t width{ 200 };
        constexpr int32_t height{ 50 };
        constexpr int32_t text_size{ 24 };
        const sf::Font font{ this -> font };
        const sf::Color idleColor{ sf::Color::Green };
        const sf::Color hoverColor{ sf::Color::Red };
        const sf::Color activeColor{ sf::Color::Blue };

        // Start game button
        auto game_button{ 
            widget::Button( 
                x_pos, 540, width, height, font, "Start Game", 
                idleColor, hoverColor, activeColor ) 
        };
        game_button.setTextSize( text_size );
        auto game_action = [ this ]{
            this -> game_window -> states.push( std::make_unique<state::Game>( state::Game( game_window ) ) );
        };
        game_button.setAction( game_action );
        game_button.pack( game_window );

        // Scores button
        auto scores_button{ 
            widget::Button( 
                x_pos, 620, width, height, font, "Scores", 
                idleColor, hoverColor, activeColor ) 
        };
        scores_button.setTextSize( text_size );
        scores_button.pack( this -> game_window );

        // Settings button
        auto settings_button{ 
            widget::Button( 
                x_pos, 700, width, height, font, "Settings", 
                idleColor, hoverColor, activeColor ) 
        };
        settings_button.setTextSize( text_size );
        settings_button.pack( this -> game_window );

        // Quit button
        auto quit_button{ 
            widget::Button( 
                x_pos, 780, width, height, font, "Quit", 
                idleColor, hoverColor, activeColor ) 
        };
        quit_button.setTextSize( text_size );
        quit_button.setAction( [ this ]{ this -> game_window -> close(); } );
        quit_button.pack( game_window );
    }
}