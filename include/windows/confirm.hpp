//====================================================
//     File data
//====================================================
/**
 * @file confirm.hpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2022-12-16
 * @copyright Copyright (c) 2022 Gianluca Bianco under the MIT license.
 */

//====================================================
//     Preprocessor directives
//====================================================
#pragma once
#ifndef SNAKE_GAME_CONFIRM_WINDOW
#define SNAKE_GAME_CONFIRM_WINDOW

//====================================================
//     Headers
//====================================================

// Windows
#include <windows/base.hpp>

namespace snake::window{

    //====================================================
    //     ConfirmWindow
    //====================================================
    /**
     * @brief Class used to create the confirm window.
     * 
     */
    class ConfirmWindow: public BaseWindow{

        //====================================================
        //     Public
        //====================================================
        public:

            // Constructors
            ConfirmWindow();

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