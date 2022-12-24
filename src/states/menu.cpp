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
        menu_texture.loadFromFile( "img/logo.png" );

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

        // Start game button
        auto game_button{ 
            widget::Button( 
                460, 540, 170, 50, this -> font, "Start Game", 
                sf::Color::Green, sf::Color::Red, sf::Color::Blue ) 
        };
        game_button.setTextSize( 20 );
        game_button.pack( game_window );

        // Scores button

        // Options button

        // Exit button
    }
}