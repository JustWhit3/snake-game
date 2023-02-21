//====================================================
//     File data
//====================================================
/**
 * @file pause_state.hpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2023-03-21
 * @copyright Copyright (c) 2022 Gianluca Bianco under the MIT license.
 */

//====================================================
//     Preprocessor directives
//====================================================
#pragma once
#ifndef SNAKE_GAME_PAUSE_STATE
#define SNAKE_GAME_PAUSE_STATE

//====================================================
//     Headers
//====================================================

// Windows
#include <windows/pause_window.hpp>

// States
#include <states/state.hpp>

namespace snake::state{

    //====================================================
    //     Pause
    //====================================================
    /**
     * @brief Class used to create the pause state.
     * 
     */
    class PauseState: public State{

        //====================================================
        //     Public
        //====================================================
        public:

            // Constructors
            PauseState( window::PauseWindow* pause_window );

            // Methods
            void drawState() override;

        //====================================================
        //     Private
        //====================================================
        private:

            // Methods
            void drawWidgets() override;
            void setWidgetsKeys() const override;
            void packWidgets() override;

            // Variables
            window::PauseWindow* pause_window;
    };
}

#endif