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

// States
#include <states/pause_state.hpp>
#include <states/loose_state.hpp>

// Utility
#include <utility/gui.hpp>

// SFML
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <SFML/Window/Keyboard.hpp>

namespace snake::window{

    //====================================================
    //     ConfirmWindow
    //====================================================
    /**
     * @brief Default constructor of the class. It creates the confirm window.
     * 
     */
    PauseWindow::PauseWindow( std::string_view status ){
    
        // Initialize window parameters
        this -> create(
            sf::VideoMode( 
                utility::getDesktopMode().width / 4, 
                utility::getDesktopMode().height / 4, 
                utility::getDesktopMode().bitsPerPixel ), 
                "", sf::Style::Titlebar | sf::Style::Close
        );
    
        // Center the window in the screen
        this -> setPosition(
            sf::Vector2i(
                this -> desktop.width * 0.5 - this -> getSize().x * 0.5, 
                this -> desktop.height * 0.5 - this -> getSize().y * 0.5
            ) 
        );

        // Push the Pause state
        if( status == "Pause" ){
            this -> pause_window_states.insert( { status, std::make_shared<state::PauseState>( state::PauseState( this ) ) } );
        }
        else if( status == "GameOver" ){
            this -> pause_window_states.insert( { status, std::make_shared<state::LooseState>( state::LooseState( this ) ) } );
        }
        
    
        // Running the window
        while( this -> isOpen() ){

            // Run the window
            runWindow();

            // Draw the first element of the states map
            this -> pause_window_states.begin() -> second -> drawState();
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
                    eventClosed();
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
    //     eventClosed
    //====================================================
    /**
     * @brief Method used to deal with the the event closed case.
     * 
     */
    void PauseWindow::eventClosed(){

        // Pause state
        if( pause_window_states.begin() -> first == "Pause" ){
            this -> close();
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
                if( this -> pause_window_states.begin() -> first == "Pause" ){
                    this -> close();
                }
                break;
            default:
                break;
        }
    }
}