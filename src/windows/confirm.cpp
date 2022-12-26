//====================================================
//     File data
//====================================================
/**
 * @file confirm.cpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2022-12-16
 * @copyright Copyright (c) 2022 Gianluca Bianco under the MIT license.
 */

//====================================================
//     Headers
//====================================================

// Windows
#include <windows/confirm.hpp>

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
            sf::VideoMode( this -> desktop.height - 500, this -> desktop.height - 500, this -> desktop.bitsPerPixel ), 
            "Quit the game"
        );
    
        // Center thw window in the screen
        this -> setPosition(
            sf::Vector2i(
                this -> desktop.width * 0.5 - this -> getSize().x * 0.5 + 500, 
                this -> desktop.height * 0.5 - this -> getSize().y * 0.5 + 700
            ) 
        );
    
        // Running the window
        runWindow();
    }
    
    //====================================================
    //     runWindow
    //====================================================
    /**
     * @brief Method used to run the main window.
     * 
     */
    void ConfirmWindow::runWindow(){
    
        // Running the main loop
        while( this -> isOpen() ){
        
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
    }
}