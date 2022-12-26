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
#include <states/game.hpp>

// SFML
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

// STD
#include <memory>

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
            sf::VideoMode( this -> desktop.height, this -> desktop.height, this -> desktop.bitsPerPixel ), 
            "Snake Game"
        );

        // Setting the icon
        auto icon = sf::Image{};
        icon.loadFromFile( "img/logo_icon.png" );
        this -> setIcon( icon.getSize().x, icon.getSize().y, icon.getPixelsPtr() );
    
        // Other settings
        this -> setPosition( sf::Vector2i( 
                this -> desktop.width * 0.5 - this -> getSize().x * 0.5, 
                this -> desktop.height * 0.5 - this -> getSize().y * 0.5 
            ) 
        );
        this -> setKeyRepeatEnabled( false );

        // Push the Menu state
        this -> states.push( std::make_unique<state::Menu>( state::Menu( this ) ) );
    
        // Display the window
        while( this -> isOpen() ){
            runWindow();
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
                case sf::Event::Closed:
                    //auto confirm_window{ ConfirmWindow() };
                    this -> close();
                    break;
                        
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
            states.top() -> drawState();
        }
    }
}