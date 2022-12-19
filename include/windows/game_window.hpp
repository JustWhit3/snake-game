//====================================================
//     File data
//====================================================
/**
 * @file game_window.hpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2022-12-19
 * @copyright Copyright (c) 2022 Gianluca Bianco under the MIT license.
 */

//====================================================
//     Headers
//====================================================

// Graphics
#include <SFML/Graphics.hpp>

//====================================================
//     GameWindow
//====================================================
/**
 * @brief Class used to create the game window. 
 * 
 */
class GameWindow: public sf::RenderWindow{

    // Public part
    public:
        GameWindow();
        void runWindow();
        void createObjects();

    // Private part
    private:
        const sf::VideoMode desktop{ sf::VideoMode::getDesktopMode() };
        const sf::Color background_color{ sf::Color::Black };
};