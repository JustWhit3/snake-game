//====================================================
//     File data
//====================================================
/**
 * @file utility.cpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2022-12-30
 * @copyright Copyright (c) 2022 Gianluca Bianco under the MIT license.
 */

//====================================================
//     Headers
//====================================================

// Utility
#include <utility/gui.hpp>

namespace snake::utility{

    //====================================================
    //     getDesktopMode
    //====================================================
    /**
     * @brief Function used to get the current desktop mode.
     * 
     * @return sf::VideoMode the desktop mode.
     */
    sf::VideoMode getDesktopMode(){
        return sf::VideoMode( 
            sf::VideoMode::getDesktopMode().height, 
            sf::VideoMode::getDesktopMode().height, 
            sf::VideoMode::getDesktopMode().bitsPerPixel
        );
    }
}