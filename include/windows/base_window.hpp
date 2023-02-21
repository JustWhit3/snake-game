//====================================================
//     File data
//====================================================
/**
 * @file base_window.hpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2022-12-26
 * @copyright Copyright (c) 2022 Gianluca Bianco under the MIT license.
 */

//====================================================
//     Preprocessor directives
//====================================================
#pragma once
#ifndef SNAKE_GAME_BASE_WINDOW
#define SNAKE_GAME_BASE_WINDOW

//====================================================
//     Headers
//====================================================

// States
#include <states/state.hpp>

// SFML
#include <SFML/Graphics.hpp>

// STD
#include <memory>
#include <map>
#include <string_view>

namespace snake::window{

    //====================================================
    //     BaseWindow
    //====================================================
    /**
     * @brief Base window class, with all the things in common with the others.
     * 
     */
    class BaseWindow: public sf::RenderWindow{

        //====================================================
        //     Public
        //====================================================
        public:

            // Constants
            const sf::VideoMode desktop{ sf::VideoMode::getDesktopMode() };

            // Variables
            std::map<std::string_view, std::shared_ptr<state::State>> game_window_states;
            std::map<std::string_view, std::shared_ptr<state::State>> pause_window_states;

        //====================================================
        //     Protected
        //====================================================
        protected:

            // Destructor
            virtual ~BaseWindow();
        
        //====================================================
        //     Private
        //====================================================
        private:

            // Methods
            virtual void eventKeyPressed( const sf::Event& event ) = 0;
    };
}

#endif