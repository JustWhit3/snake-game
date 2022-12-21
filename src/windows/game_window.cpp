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
//     Preprocessor directives
//====================================================

// ptc-print
#define PTC_ENABLE_PERFORMANCE_IMPROVEMENTS
#define PTC_DISABLE_STD_TYPES_PRINTING

//====================================================
//     Headers
//====================================================

// My headers
#include <windows/game_window.hpp>
#include <windows/confirm_window.hpp>

// Other headers
#include <ptc/print.hpp>

// Graphics
#include <SFML/Window.hpp>

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
    
        // Center the window in the screen
        this -> setPosition(
            sf::Vector2i(
                desktop.width * 0.5 - this -> getSize().x * 0.5, 
                desktop.height * 0.5 - this -> getSize().y * 0.5
            ) 
        );
    
        // Setting the icon
        auto icon = sf::Image{};
        icon.loadFromFile( "img/logo_icon.png" );
        this -> setIcon( icon.getSize().x, icon.getSize().y, icon.getPixelsPtr() );
    
        // Other settings
        this -> setKeyRepeatEnabled( false );
    
        // Run the main loop
        while( this -> isOpen() ){
            displayMenuFrame();
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
            }
    }
    
    //====================================================
    //     createObjects
    //====================================================
    void GameWindow::displayMenuFrame(){
    
            // Clear the window
            this -> clear( background_color );
    
            // Drawing the title
            sf::Texture logo_texture;
            logo_texture.loadFromFile( "img/logo.png" );
            sf::Sprite logo_sprite;
            logo_sprite.setTexture( logo_texture, true );
            const sf::Vector2f logo_targetSize( 500, 400 ); 
            logo_sprite.setScale(
                logo_targetSize.x / logo_sprite.getLocalBounds().width,
                logo_targetSize.y / logo_sprite.getLocalBounds().height
            );
            this -> draw( logo_sprite );

            // Drawing widgets
    
            // End the current frame
            this -> display();
    }
}