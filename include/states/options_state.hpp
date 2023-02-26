//====================================================
//     File data
//====================================================
/**
 * @file options_state.hpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2022-12-24
 * @copyright Copyright (c) 2022 Gianluca Bianco under the MIT license.
 */

//====================================================
//     Preprocessor directives
//====================================================
#pragma once
#ifndef SNAKE_GAME_OPTIONS_STATE
#define SNAKE_GAME_OPTIONS_STATE

//====================================================
//     Headers
//====================================================

// Windows
#include <windows/game_window.hpp>

// Widgets
#include <widgets/textbox.hpp>

namespace snake::state{

    //====================================================
    //     OptionsState
    //====================================================
    /**
     * @brief Class used to create the options menu.
     * 
     */
    class OptionsState: public State{

        //====================================================
        //     Public
        //====================================================
        public:

            // Constructors
            OptionsState( window::GameWindow* game_window );

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
            void updateEnteredText();

            // Variables
            window::GameWindow* game_window;
            sf::Text back_to_menu;
            sf::Text player_name_text;
            sf::String player_name_input;
            std::string player_name_current;
            std::shared_ptr<widget::Textbox> player_name_textbox;

            // Constants
            const uint64_t game_window_size_x = this -> game_window -> getSize().x;
            const uint64_t game_window_size_y = this -> game_window -> getSize().y;
    };
}

#endif