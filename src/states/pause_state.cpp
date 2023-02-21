//====================================================
//     File data
//====================================================
/**
 * @file pause_state.cpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2022-12-22
 * @copyright Copyright (c) 2022 Gianluca Bianco under the MIT license.
 */

//====================================================
//     Preprocessor directives
//====================================================

// ptc-print
#ifdef DEBUG_SNAKE_GAME
    #define PTC_ENABLE_PERFORMANCE_IMPROVEMENTS
    #define PTC_DISABLE_STD_TYPES_PRINTING
#endif

//====================================================
//     Headers
//====================================================

// Windows
#include <windows/pause_window.hpp>

// States
#include <states/state.hpp>
#include <states/pause_state.hpp>

// Debug
#ifdef DEBUG_SNAKE_GAME
    #include <ptc/print.hpp>
#endif

namespace snake::state{

    //====================================================
    //     Pause (constructor)
    //====================================================
    /**
     * @brief Constructor of the Pause class.
     * 
     * @param pause_window The window to which the state stuff is constructed.
     */
    PauseState::PauseState( window::PauseWindow* pause_window ): 
        pause_window( pause_window ){

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
    void PauseState::drawState() {

        // Clear the window
        this -> pause_window -> clear( this -> background_color );

        // Drawing widgets
        this -> setWidgetsKeys();
        this -> packWidgets();

        // Display the state
        this -> pause_window -> display();
    }

    //====================================================
    //     drawWidgets
    //====================================================
    /**
     * @brief Method used to draw widgets in the current state.
     * 
     */
    void PauseState::drawWidgets() {

    }

    //====================================================
    //     setWidgetsKeys
    //====================================================
    /**
     * @brief Method used to set widgets in the current state.
     * 
     */
    void PauseState::setWidgetsKeys() const {

    }

    //====================================================
    //     packWidgets
    //====================================================
    /**
     * @brief Method used to pack widgets in the current state.
     * 
     */
    void PauseState::packWidgets(){
        
    }
}