//====================================================
//     File data
//====================================================
/**
 * @file game.cpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2022-12-19
 * @copyright Copyright (c) 2022 Gianluca Bianco under the MIT license.
 */

//====================================================
//     Headers
//====================================================

// Windows
#include <windows/game.hpp>
#include <windows/confirm.hpp>

// States
#include <states/menu.hpp>

// SFML
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

namespace snake::window{

    //====================================================
    //     GameWindow
    //====================================================
    /**
     * @brief Default constructor of the class. It creates the game window.
     * 
     */
    GameWindow::GameWindow(){
    
        // Initialize window parameters
        this -> create(
            sf::VideoMode( desktop.height, desktop.height, desktop.bitsPerPixel ), 
            "Snake Game"
        );

        // Setting the icon
        auto icon = sf::Image{};
        icon.loadFromFile( "img/logo_icon.png" );
        this -> setIcon( icon.getSize().x, icon.getSize().y, icon.getPixelsPtr() );
    
        // Other settings
        this -> setPosition( sf::Vector2i( 
                desktop.width * 0.5 - this -> getSize().x * 0.5, 
                desktop.height * 0.5 - this -> getSize().y * 0.5 
            ) 
        );
        this -> setKeyRepeatEnabled( false );
    
        // Run the main loop
        while( this -> isOpen() ){

            // Display window
            runWindow();
    
            // Move the snake
            //if( sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) ) return;
            //else if( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) ) return;
            //else if( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) ) return;
            //else if( sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) ) return;
        }
    }
    
    //====================================================
    //     runWindow
    //====================================================
    /**
     * @brief Method used to run the main window.
     * 
     */
    void GameWindow::runWindow(){
        
        // Check events of the main window
        sf::Event game_event;
        while( this -> pollEvent( game_event ) ){
        
            // Handling different events
            switch( game_event.type ){
            
                // Window closing
                case sf::Event::Closed:{
                    //auto confirm_window{ ConfirmWindow() };
                    this -> close();
                    break;
                }
                        
                // Key pressed in window
                case sf::Event::KeyPressed:
                    break;
                    
                // Window resizing
                case sf::Event::Resized:
                    break;
    
                // Pause the game if lost focus
                case sf::Event::LostFocus:
                    break;
                    
                // Resume the game if gained focus
                case sf::Event::GainedFocus:
                    break;
    
                // Default cases
                default:
                    break;
            }

            // Draw the menu
            auto menu{ state::Menu( this ) };
        }
    }
}