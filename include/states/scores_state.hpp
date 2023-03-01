//====================================================
//     File data
//====================================================
/**
 * @file scores_state.hpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2022-12-24
 * @copyright Copyright (c) 2022 Gianluca Bianco under the MIT license.
 */

//====================================================
//     Preprocessor directives
//====================================================
#pragma once
#ifndef SNAKE_GAME_SCORES_STATE
#define SNAKE_GAME_SCORES_STATE

//====================================================
//     Headers
//====================================================

// Windows
#include <windows/game_window.hpp>

// SFML
#include <SFML/Graphics/Text.hpp>

namespace snake::state{

    //====================================================
    //     OptionsState
    //====================================================
    /**
     * @brief Class used to create the scores menu.
     * 
     */
    class ScoresState: public State{

        //====================================================
        //     Public
        //====================================================
        public:

            // Constructors
            ScoresState( window::GameWindow* game_window );

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
            window::GameWindow* game_window;
            sf::Text back_to_menu;

            // Constants
            const uint64_t game_window_size_x = this -> game_window -> getSize().x;
            const uint64_t game_window_size_y = this -> game_window -> getSize().y;
    };
}

#endif