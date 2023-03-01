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

// SFML
#include <SFML/Window/Event.hpp>

// STD
#include <sstream>
#include <filesystem>
#include <cstdlib>
#include <string>

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
            std::string player_option;
            std::string speed_option;
            std::string background_option;
            std::filesystem::path options_file_path;

            // Constants
            const std::string username = getenv( "USERNAME" );

        //====================================================
        //     Private
        //====================================================
        private:

            // Methods
            void runWindow();
            void eventClosed();
            void eventKeyPressed( const sf::Event& event ) override; 

            // Variables
            std::ostringstream game_directory_oss;
            std::ostringstream options_file_oss;
    };
}

#endif