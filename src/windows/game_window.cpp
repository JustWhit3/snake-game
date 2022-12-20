//====================================================
//     File data
//====================================================
/**
 * @file game_window.cpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2022-12-19
 * @copyright Copyright (c) 2022 Gianluca Bianco under the MIT license.
 */

//====================================================
//     Headers
//====================================================

// My headers
#include <windows/game_window.hpp>
#include <windows/confirm_window.hpp>

// Graphics
#include <SFML/Window.hpp>

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

    // Center the window in the screen
    this -> setPosition(
        sf::Vector2i(
            desktop.width * 0.5 - this -> getSize().x * 0.5, 
            desktop.height * 0.5 - this -> getSize().y * 0.5
        ) 
    );

    // Other settings
    this -> setKeyRepeatEnabled( false );

    // Run the main loop
    while( this -> isOpen() ){
        runWindow();
        createObjects();

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
        }
}

//====================================================
//     createObjects
//====================================================
void GameWindow::createObjects(){

        // Clear the window
        this -> clear( background_color );

        // Draw objects

        // End the current frame
        this -> display();
}