//====================================================
//     File data
//====================================================
/**
 * @file menu_state.hpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2022-12-22
 * @copyright Copyright (c) 2022 Gianluca Bianco under the MIT license.
 */

//====================================================
//     Preprocessor directives
//====================================================
#pragma once
#ifndef SNAKE_GAME_MENU_STATE
#define SNAKE_GAME_MENU_STATE

//====================================================
//     Headers
//====================================================

// Windows
#include <windows/game_window.hpp>

// States
#include <states/state.hpp>

// Widgets
#include <widgets/button.hpp>

// SFML
#include <SFML/Graphics.hpp>

// STD
#include <cstdint>

namespace snake::state{

    //====================================================
    //     Menu
    //====================================================
    /**
     * @brief Class used to create the main menu.
     * 
     */
    class MenuState: public State{

        //====================================================
        //     Public
        //====================================================
        public:

            // Constructors
            MenuState( window::GameWindow* game_window );

            // Methods
            void drawState() override;

        //====================================================
        //     Private
        //====================================================
        private:

            // Methods
            void drawImg();
            void drawWidgets() override;
            void loadSounds();
            void setWidgetsKeys() const override;
            void packWidgets() override;

            // Variables
            window::GameWindow* game_window;
            std::shared_ptr<widget::Button> quit_button;
            std::shared_ptr<widget::Button> game_button;
            std::shared_ptr<widget::Button> scores_button;
            std::shared_ptr<widget::Button> settings_button;
            sf::Text metadata;
            sf::Sprite logo_sprite;
            sf::Sprite snake_branch_sprite;
            sf::RectangleShape background;

            // Constants
            const uint64_t game_window_size_x = this -> game_window -> getSize().x;
            const uint64_t game_window_size_y = this -> game_window -> getSize().y;
    };
}

#endif