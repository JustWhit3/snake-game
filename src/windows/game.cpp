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
            "Snake Game", sf::Style::Titlebar | sf::Style::Close
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
        //this -> states.push( std::make_unique<state::Menu>( state::Menu( this ) ) );

        this -> states.insert( { "Menu", std::make_unique<state::Menu>( state::Menu( this ) ) } );
    
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
                    eventClosed();
                    break;
                        
                // Key pressed in window
                case sf::Event::KeyPressed:
                    eventKeyPressed( game_event );
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

            // Draw the first element of the states map
            this -> states.begin() -> second -> drawState();
        }
    }

    //====================================================
    //     eventClosed
    //====================================================
    /**
     * @brief Method used to deal with the the event closed case.
     * 
     */
    void GameWindow::eventClosed(){

        // Menu state
        if( states.begin() -> first == "Menu" ){
            this -> close();
        }

        // Game state
        else if( states.begin() -> first == "Game" ){
            auto confirm_window{ ConfirmWindow() };
        }
    }

    //====================================================
    //     eventKeyPressed
    //====================================================
    /**
     * @brief Method used to deal with the the event key pressed case.
     * 
     */
    void GameWindow::eventKeyPressed( const sf::Event& event ){

        // Menu state
        if( states.begin() -> first == "Menu" ){
            switch( event.key.code ){
                case sf::Keyboard::Escape: // Esc
                    this -> close();
                    break;
                default:
                    break;
            }
        }
    }
}