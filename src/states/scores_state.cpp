//====================================================
//     File data
//====================================================
/**
 * @file scores_state.cpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2022-12-24
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
#include <windows/game_window.hpp>

// States
#include <states/state.hpp>
#include <states/scores_state.hpp>

// SFML
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

// STD
#include <memory>


namespace snake::state{

    //====================================================
    //     OptionsState (constructor)
    //====================================================
    /**
     * @brief Constructor of the ScoresState class.
     * 
     * @param game_window The window to which the state stuff is constructed.
     */
    ScoresState::ScoresState( window::GameWindow* game_window ): 
        game_window( game_window ){

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
    void ScoresState::drawState() {

        // Clear the window
        this -> game_window -> clear( this -> background_color );

        // Drawing images
        this -> drawImg();

        // Drawing widgets
        this -> setWidgetsKeys();
        this -> packWidgets();

        // Display the state
        this -> game_window -> display();
    }

    //====================================================
    //     drawImg
    //====================================================
    /**
     * @brief Method used to draw the images.
     * 
     */
    void ScoresState::drawImg() const {

        // Loading files from textures
        if( ! state_texture_1.loadFromFile( "img/images/snake_branch.png" ) ){
            this -> game_window -> close();
        }
        if( ! state_texture_2.loadFromFile( "img/images/menu_background.jpg" ) ){
            this -> game_window -> close();
        }

        // Snake on the branch
        sf::Sprite snake_branch_sprite( state_texture_1 );
        snake_branch_sprite.setPosition( 
           0, 
           ( this -> game_window_size_y - snake_branch_sprite.getGlobalBounds().height ) * 0.25f
        );

        // Background
        sf::RectangleShape background( sf::Vector2f( this -> game_window_size_x, this -> game_window_size_y ) );
        background.setTexture( &state_texture_2, true );

        // Drawing the images
        this -> game_window -> draw( background );
        this -> game_window -> draw( snake_branch_sprite );
    }

    //====================================================
    //     drawWidgets
    //====================================================
    /**
     * @brief Method used to draw widgets in the current state.
     * 
     */
    void ScoresState::drawWidgets() {

        // Back-to-menu text
        this -> back_to_menu.setFillColor( sf::Color::Black );
        this -> back_to_menu.setPosition( 
            this -> game_window -> getSize().x * 0.03f, 
            this -> game_window -> getSize().y * 0.91f 
        );
        this -> back_to_menu.setCharacterSize( 30 );
    }

    //====================================================
    //     setWidgetsKeys
    //====================================================
    /**
     * @brief Method used to set widgets in the current state.
     * 
     */
    void ScoresState::setWidgetsKeys() const {

    }

    //====================================================
    //     packWidgets
    //====================================================
    /**
     * @brief Method used to pack widgets in the current state.
     * 
     */
    void ScoresState::packWidgets(){

        // Back-to-menu text settings
        this -> back_to_menu.setFont( this -> font );
        this -> back_to_menu.setString( "Press <Tab> to back to menu" );

        // Draw stuff
        this -> game_window -> draw( this -> back_to_menu );
    }
}