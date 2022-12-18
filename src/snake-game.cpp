//====================================================
//     File data
//====================================================
/**
 * @file app.cpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2022-12-16
 * @copyright Copyright (c) 2022 Gianluca Bianco under the MIT license.
 */

//====================================================
//     Headers
//====================================================

// Graphics
#include <SFML/Window.hpp>

//====================================================
//     main
//====================================================
int main(){

    // Creating the main window with the same pixel depth as the desktop
    sf::Window main_window;
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    main_window.create(
        sf::VideoMode( 1024, 1024, desktop.bitsPerPixel ), 
        "Snake Game"
    );

    // Centering the main window in the screen
    main_window.setPosition(
        sf::Vector2i(
            sf::VideoMode::getDesktopMode().width * 0.5 - main_window.getSize().x * 0.5, 
            sf::VideoMode::getDesktopMode().height * 0.5 - main_window.getSize().y * 0.5
        ) 
    );

    // Running the main loop
    while( main_window.isOpen() ){

        // Check events of the main window
        sf::Event event;
        while( main_window.pollEvent( event ) ){

            // Close the window if required
            if( event.type == sf::Event::Closed ){
                main_window.close();
            }
        }
    }
}