//====================================================
//     File data
//====================================================
/**
 * @file pause_window.hpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2022-12-16
 * @copyright Copyright (c) 2022 Gianluca Bianco under the MIT license.
 */

//====================================================
//     Preprocessor directives
//====================================================
#pragma once
#ifndef SNAKE_GAME_PAUSE_WINDOW
#define SNAKE_GAME_PAUSE_WINDOW

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
    //     ConfirmWindow
    //====================================================
    /**
     * @brief Class used to create the confirm window.
     * 
     */
    class PauseWindow: public BaseWindow{

        //====================================================
        //     Public
        //====================================================
        public:

            // Constructors
            PauseWindow();

        //====================================================
        //     Private
        //====================================================
        private:

            // Methods
            void runWindow();
            void eventClosed() override;
            void eventKeyPressed( const sf::Event& event ) override;
    };
}

#endif