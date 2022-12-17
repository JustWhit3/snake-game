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

    // Creating a window with the same pixel depth as the desktop
    sf::Window main_window;
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    main_window.create( sf::VideoMode( 1024, 768, desktop.bitsPerPixel ), "Snake Game" );

    // Running the main window
    while( main_window.isOpen() ){
        continue;
    }
}