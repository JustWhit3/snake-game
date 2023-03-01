//====================================================
//     File data
//====================================================
/**
 * @file game_state.hpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2022-12-25
 * @copyright Copyright (c) 2022 Gianluca Bianco under the MIT license.
 */

//====================================================
//     Preprocessor directives
//====================================================
#pragma once
#ifndef SNAKE_GAME_GAME_STATE
#define SNAKE_GAME_GAME_STATE

//====================================================
//     Headers
//====================================================

// Windows
#include <windows/game_window.hpp>

// States
#include <states/state.hpp>

// Entities
#include <entities/snake.hpp>
#include <entities/food.hpp>

// SFML
#include <SFML/Graphics/Text.hpp>

// STD
#include <cstdint>
#include <memory>
#include <sstream>
#include <filesystem>

namespace snake::state{

    //====================================================
    //     Game
    //====================================================
    /**
     * @brief Class used to create the game state.
     * 
     */
    class GameState: public State{

        //====================================================
        //     Public
        //====================================================
        public:

            // Constructors
            GameState( window::GameWindow* game_window );

            // Methods
            void drawState() override;

        //====================================================
        //     Private
        //====================================================
        private:

            // Methods
            void drawEntities() const;
            void updateEntities();
            void gameRules();
            void drawWidgets() override;
            void packWidgets() override;
            void gameOver();
            int64_t computeBestScore();

            // Variables
            window::GameWindow* game_window;
            std::unique_ptr<entity::Snake> snake{ std::make_unique<entity::Snake>( entity::Snake( game_window ) ) };
            std::unique_ptr<entity::Food> food{ std::make_unique<entity::Food>( entity::Food( game_window ) ) };
            uint64_t score{ 0 };
            sf::Text score_update;
            sf::Text best_score_text;
            sf::Text current_player_text;
            sf::Vertex horizontal_line[2];
            sf::Sprite score_icon;
            sf::Sprite best_score_icon;
            sf::RectangleShape background;
            sf::RectangleShape title_background;
            std::ostringstream score_file_oss;
            std::filesystem::path score_file_path;
            std::filesystem::path options_file_path;
            std::ostringstream options_file_oss;
            std::filesystem::path background_file;

            // Constants
            const uint32_t horizontal_line_y_coord = this -> game_window -> getSize().x / 24;
            const uint32_t window_x_max = this -> game_window -> getSize().x;
            const uint32_t window_y_max = this -> game_window -> getSize().y;
    };
}

#endif