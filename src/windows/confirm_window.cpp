//====================================================
//     File data
//====================================================
/**
 * @file confirm_window.cpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2022-12-16
 * @copyright Copyright (c) 2022 Gianluca Bianco under the MIT license.
 */

//====================================================
//     Headers
//====================================================

// Windows
#include <windows/confirm_window.hpp>

// SFML
#include <SFML/Window.hpp>

namespace snake::window{

    //====================================================
    //     ConfirmWindow
    //====================================================
    /**
     * @brief Default constructor of the class. It creates the confirm window.
     * 
     */
    ConfirmWindow::ConfirmWindow(){
    
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
    void ConfirmWindow::runWindow(){
    
        // Check events of the main window
        sf::Event confirm_event;
        while( this -> pollEvent( confirm_event ) ){
        
            // Handling different events
            switch( confirm_event.type ){
            
                // Window closing
                case sf::Event::Closed:{
                    this -> close();
                    break;
                }

                // Default cases
                default:
                    break;
            }
        }
    }

    //====================================================
    //     eventClosed
    //====================================================
    /**
     * @brief Method used to deal with the the event closed case.
     * 
     */
    void ConfirmWindow::eventClosed(){

    }

    //====================================================
    //     eventKeyPressed
    //====================================================
    /**
     * @brief Method used to deal with the the event key pressed case.
     * 
     */
    void ConfirmWindow::eventKeyPressed( const sf::Event& event ){
        ( void ) event;
    }
}