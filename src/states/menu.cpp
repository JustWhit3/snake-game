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

// Widgets
#include <widgets/button.hpp>

// STD
#include <cstdlib>

namespace snake::state{

    //====================================================
    //     Static variables
    //====================================================
    sf::Texture Menu::menu_texture;

    //====================================================
    //     Menu (constructor)
    //====================================================
    /**
     * @brief Main constructor of the Menu class. It constructs the main menu.
     * 
     * @param game_window The window to which the frame is drawn.
     */
    Menu::Menu( window::GameWindow* game_window ){
        
            // Clear the window
            game_window -> clear( game_window -> background_color );

            // Drawing images
            drawLogo( game_window );

            // Drawing widgets
            drawWidgets( game_window );
    
            // End the current frame
            game_window -> display();
    }

    //====================================================
    //     drawLogo
    //====================================================
    /**
     * @brief Method used to draw the image logo.
     * 
     * @param game_window The window to which the frame is drawn.
     */
    void Menu::drawLogo( window::GameWindow* game_window ) const {

        // Creating the texture
        if( ! menu_texture.loadFromFile( "img/logo.png" ) ){
            std::exit( 0 );
        }

        // Creating the sprite
        sf::Sprite logo_sprite;
        logo_sprite.setTexture( menu_texture, true );
        logo_sprite.setPosition( sf::Vector2f( 280, 120 ) );

        // Drawing the image
        game_window -> draw( logo_sprite );
    }

    //====================================================
    //     drawWidgets
    //====================================================
    void Menu::drawWidgets( window::GameWindow* game_window ) const {

        // Common button settings
        constexpr int32_t x_pos{ 460 };
        constexpr int32_t width{ 170 };
        constexpr int32_t height{ 50 };
        constexpr int32_t text_size{ 20 };
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
        game_button.pack( game_window );

        // Scores button
        auto scores_button{ 
            widget::Button( 
                x_pos, 620, width, height, font, "Scores", 
                idleColor, hoverColor, activeColor ) 
        };
        scores_button.setTextSize( text_size );
        scores_button.pack( game_window );

        // Settings button
        auto settings_button{ 
            widget::Button( 
                x_pos, 700, width, height, font, "Settings", 
                idleColor, hoverColor, activeColor ) 
        };
        settings_button.setTextSize( text_size );
        settings_button.pack( game_window );

        // Quit button
        auto quit_button{ 
            widget::Button( 
                x_pos, 780, width, height, font, "Quit", 
                idleColor, hoverColor, activeColor ) 
        };
        quit_button.setTextSize( text_size );
        quit_button.setAction( [ game_window ]{ game_window -> close(); } );
        quit_button.pack( game_window );
    }
}