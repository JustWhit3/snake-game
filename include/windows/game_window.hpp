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
#include <fstream>
#include <array>

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

            // Methods
            std::string processInputFile( std::ifstream input_stream, int16_t row_n, int16_t pos );

            // Variables
            sf::Event game_event;
            std::string player_option;
            std::string speed_option;
            std::string background_option;
            std::filesystem::path options_file_path;
            std::filesystem::path score_file_path;
            std::vector<uint64_t> scores_container;

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
            std::vector<uint64_t> getScoresContainer() const;
            void createGameFiles();

            // Variables
            std::ostringstream game_directory_oss;
            std::ostringstream options_file_oss;
            std::ostringstream score_file_oss;

            std::string input;
            std::array<std::string, 2> strings;
            std::vector<std::string> lines;
            std::stringstream words;
    };
}

#endif