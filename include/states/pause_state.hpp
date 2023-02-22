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
#include <windows/game_window.hpp>

// States
#include <states/state.hpp>

// Widgets
#include <widgets/button.hpp>

// STD
#include <memory>

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
            void drawImg() const;
            void drawWidgets() override;
            void setWidgetsKeys() const override;
            void packWidgets() override;

            // Variables
            window::PauseWindow* pause_window;
            std::shared_ptr<widget::Button> yes_button;
            std::shared_ptr<widget::Button> no_button;
            sf::Text text;

            // Constants
            const uint64_t pause_window_size_x = this -> pause_window -> getSize().x;
            const uint64_t pause_window_size_y = this -> pause_window -> getSize().y;
    };
}

#endif