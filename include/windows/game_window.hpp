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
//     Preprocessor directives
//====================================================
#pragma once
#ifndef SNAKE_GAME_GAME_WINDOW
#define SNAKE_GAME_GAME_WINDOW

//====================================================
//     Headers
//====================================================

// Windows
#include <windows/base_window.hpp>

// Required by IWYU
namespace sf { 
    class Event;
}

namespace snake::window{

    //====================================================
    //     GameWindow
    //====================================================
    /**
     * @brief Class used to create the game window. 
     * 
     */
    class GameWindow: public BaseWindow{

        //====================================================
        //     Public
        //====================================================
        public:

            // Constructors
            GameWindow();

            // Variables
            sf::Event game_event;

        //====================================================
        //     Private
        //====================================================
        private:

            // Methods
            void runWindow();
            void eventClosed();
            void eventKeyPressed( const sf::Event& event ) override;
    };
}

#endif