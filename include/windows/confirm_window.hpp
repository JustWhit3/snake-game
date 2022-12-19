//====================================================
//     File data
//====================================================
/**
 * @file confirm_window.hpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2022-12-16
 * @copyright Copyright (c) 2022 Gianluca Bianco under the MIT license.
 */

//====================================================
//     Headers
//====================================================

// Graphics headers
#include <SFML/Window.hpp>

//====================================================
//     ConfirmWindow
//====================================================
/**
 * @brief Class used to create the confirm window.
 * 
 */
class ConfirmWindow: public sf::Window{

    // Public part
    public:
        ConfirmWindow();
        void runWindow();

    // Private part
    private:
        const sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
};