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
#include <SFML/Graphics/Sprite.hpp>

// STD
#include <vector>
#include <map>

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
            void drawImg();
            void drawWidgets() override;
            void packWidgets() override;
            std::multimap<uint64_t, std::string, std::greater<int64_t>> getScoresMap();
            void initStrings();

            // Variables
            window::GameWindow* game_window;
            sf::Text back_to_menu;
            sf::Text first_player;
            sf::Text second_player;
            sf::Text third_player;
            std::multimap<uint64_t, std::string, std::greater<int64_t>> scores_map;
            sf::Sprite gold_trophy;
            sf::Sprite silver_trophy;
            sf::Sprite bronze_trophy;
            sf::Sprite title;
            std::string string_first;
            std::string string_second;
            std::string string_third;
            std::multimap<uint64_t, std::string, std::greater<int64_t>>::iterator iterator;

            // Constants
            const uint64_t game_window_size_x = this -> game_window -> getSize().x;
            const uint64_t game_window_size_y = this -> game_window -> getSize().y;
    };
}

#endif