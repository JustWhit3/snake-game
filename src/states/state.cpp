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

// STD
#include <cstdlib>

namespace snake::state{

    //====================================================
    //     Static variables
    //====================================================
    sf::Texture State::menu_texture;

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
    //     drawWidgets
    //====================================================
    /**
     * @brief Method used to draw widgets in the current state.
     * 
     */
    void State::drawWidgets() const {

    }

}
