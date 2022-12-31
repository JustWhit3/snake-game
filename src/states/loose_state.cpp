//====================================================
//     File data
//====================================================
/**
 * @file loose_state.cpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2022-12-31
 * @copyright Copyright (c) 2022 Gianluca Bianco under the MIT license.
 */

//====================================================
//     Headers
//====================================================

// States
#include <states/loose_state.hpp>

namespace snake::state{

    //====================================================
    //     Menu (constructor)
    //====================================================
    /**
     * @brief Constructor of the Loose class.
     * 
     * @param game_window The window to which the state stuff is constructed.
     */
    LooseState::LooseState( window::GameWindow* game_window ): 
        game_window( game_window ){

        // Define state properties
        this -> state_dimension.setSize( sf::Vector2f( 100.0f, 100.0f ) );
        this -> state_dimension.setFillColor( sf::Color::White );
        this -> state_dimension.setOutlineColor( sf::Color::Black );
        this -> state_dimension.setOutlineThickness( 2 );
        //this -> state_dimension.setPosition( 530.f, 900.f );

        // Draw widgets
        this -> drawWidgets();

    }

    //====================================================
    //     drawState
    //====================================================
    /**
     * @brief Method used to draw the current state.
     * 
     */
    void LooseState::drawState() {

        // Draw state
        this -> game_window -> draw( state_dimension );

        // Drawing widgets
        this -> setWidgetsKeys();
        this -> packWidgets();

        // Display the state
        this -> game_window -> display();
    }

    //====================================================
    //     drawWidgets
    //====================================================
    /**
     * @brief Method used to draw widgets in the current state.
     * 
     */
    void LooseState::drawWidgets() {
    
    }

    //====================================================
    //     setWidgets
    //====================================================
    /**
     * @brief Method used to set widgets in the current state.
     * 
     */
    void LooseState::setWidgetsKeys() const {

    }

    //====================================================
    //     packWidgets
    //====================================================
    /**
     * @brief Method used to pack widgets in the current state.
     * 
     */
    void LooseState::packWidgets(){

    }
    
}