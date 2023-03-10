//====================================================
//     File data
//====================================================
/**
 * @file state.cpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2022-12-26
 * @copyright Copyright (c) 2022 Gianluca Bianco under the MIT license.
 */

//====================================================
//     Headers
//====================================================

// States
#include <states/state.hpp>

// SFML
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/Font.hpp>

// STD
#include <cstdlib>
#include <memory> 

namespace snake::state{

    //====================================================
    //     Static variables
    //====================================================
    sf::Texture State::state_texture_1;
    sf::Texture State::state_texture_2;
    sf::Texture State::state_texture_3;
    sf::Texture State::state_texture_4;
    sf::Texture State::state_texture_5;
    sf::Texture State::state_texture_6;
    sf::Texture State::state_texture_7;
    sf::Font State::font;

    //====================================================
    //     State (constructor)
    //====================================================
    /**
     * @brief Main constructor of the State class.
     * 
     */
    State::State(){
        if( ! this -> font.loadFromFile( "fonts/source-sans-pro/SourceSansPro-Semibold.otf" ) ){
            std::exit( 0 );
        };
    }

    //====================================================
    //     State (destructor)
    //====================================================
    /**
     * @brief Destructor of the State class.
     * 
     */
    State::~State(){

    }

    //====================================================
    //     setWidgetsKeys
    //====================================================
    /**
     * @brief Method used to set widgets keyboard properties in the current state.
     * 
     */
    void State::setWidgetsKeys() const {

    }
}
