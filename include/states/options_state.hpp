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

// SFML
#include <SFML/Graphics/Sprite.hpp>

// STD
#include <filesystem>
#include <fstream>

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
            void drawImg();
            void drawWidgets() override;
            void packWidgets() override;
            void fileUpdate( std::string_view option, uint16_t option_idx );

            // Variables
            window::GameWindow* game_window;
            sf::Text back_to_menu;
            std::filesystem::path options_file_path;
            sf::Sprite settings_logo;
            std::vector<std::string> lines;
            std::string input;
            
            // Player option variables
            sf::Text text_has_been_saved_player;
            sf::Text player_option;
            std::shared_ptr<widget::Textbox> player_name_textbox;
            bool already_wrote_player;

            // Speed option variables
            sf::Text text_has_been_saved_speed;
            sf::Text speed_option;
            std::shared_ptr<widget::Textbox> snake_speed_textbox;
            bool already_wrote_speed;

            // Background option variables
            sf::Text text_has_been_saved_background;
            sf::Text background_option;
            std::shared_ptr<widget::Textbox> background_textbox;
            bool already_wrote_background;

            // Constants
            const uint64_t game_window_size_x = this -> game_window -> getSize().x;
            const uint64_t game_window_size_y = this -> game_window -> getSize().y;
            const sf::Time delta_time{ sf::seconds( 1.f ) };
    };
}

#endif