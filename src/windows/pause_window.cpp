//====================================================
//     File data
//====================================================
/**
 * @file pause_window.cpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2022-12-16
 * @copyright Copyright (c) 2022 Gianluca Bianco under the MIT license.
 */

//====================================================
//     Headers
//====================================================

// Windows
#include <windows/pause_window.hpp>

// SFML
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>

namespace snake::window{

    //====================================================
    //     ConfirmWindow
    //====================================================
    /**
     * @brief Default constructor of the class. It creates the confirm window.
     * 
     */
    PauseWindow::PauseWindow(){
    
        // Initialize window parameters
        this -> create(
            sf::VideoMode( this -> desktop.height - 500.f, this -> desktop.height - 500.f, this -> desktop.bitsPerPixel ), 
            "Quit the game", sf::Style::Titlebar | sf::Style::Close
        );
    
        // Center thw window in the screen
        this -> setPosition(
            sf::Vector2i(
                this -> desktop.width * 0.5 - this -> getSize().x * 0.5 + 500.f, 
                this -> desktop.height * 0.5 - this -> getSize().y * 0.5 + 700.f
            ) 
        );
    
        // Running the window
        while( this -> isOpen() ){

            // Run the window
            runWindow();

            // Do something...
        }
    }
    
    //====================================================
    //     runWindow
    //====================================================
    /**
     * @brief Method used to run the main window.
     * 
     */
    void PauseWindow::runWindow(){
    
        // Check events of the main window
        sf::Event pause_event;
        while( this -> pollEvent( pause_event ) ){
        
            // Handling different events
            switch( pause_event.type ){
            
                // Window closing
                case sf::Event::Closed:
                    this -> close();
                    break;

                // Key pressed in window
                case sf::Event::KeyPressed:
                    eventKeyPressed( pause_event );
                    break;

                // Default cases
                default:
                    break;
            }
        }
    }

    //====================================================
    //     eventKeyPressed
    //====================================================
    /**
     * @brief Method used to deal with the the event key pressed case.
     * 
     */
    void PauseWindow::eventKeyPressed( const sf::Event& event ){
        switch( event.key.code ){
            case sf::Keyboard::Escape: // Esc
                this -> close();
                break;
            default:
                break;
        }
    }
}