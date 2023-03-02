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
#include <fstream>
#include <algorithm>

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

        // Compute best scores
        this -> scores = this -> game_window -> scores_container;
        std::sort( scores.begin(), scores.end(), std::greater<uint64_t>() );

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
    void ScoresState::drawImg(){

        // Loading files from textures
        if( ! state_texture_1.loadFromFile( "img/images/snake_branch.png" ) ){
            this -> game_window -> close();
        }
        if( ! state_texture_2.loadFromFile( "img/images/menu_background.jpg" ) ){
            this -> game_window -> close();
        }
        if( ! state_texture_3.loadFromFile( "img/textures/gold_trophy.png" ) ){
            this -> game_window -> close();
        }
        if( ! state_texture_4.loadFromFile( "img/textures/silver_trophy.jpeg" ) ){
            this -> game_window -> close();
        }
        if( ! state_texture_5.loadFromFile( "img/textures/bronze_trophy.jpeg" ) ){
            this -> game_window -> close();
        }

        // Snake on the branch
        this -> snake_branch_sprite.setTexture( this -> state_texture_1 );
        this -> snake_branch_sprite.setPosition( 
           0, 
           ( this -> game_window_size_y - snake_branch_sprite.getGlobalBounds().height ) * 0.25f
        );

        // Background
        this -> background.setSize( sf::Vector2f( this -> game_window_size_x, this -> game_window_size_y ) );
        this -> background.setTexture( &this -> state_texture_2, true );

        // First award icon
        this -> gold_trophy.setTexture( this -> state_texture_3 );
        this -> gold_trophy.setPosition( 
           ( this -> game_window_size_x * 0.5f - this -> width * 0.5f ) * 0.75, 
           ( this -> game_window_size_y * 0.5f - this -> height * 0.5f ) * 0.9f
        );

        // Second award icon
        this -> silver_trophy.setTexture( this -> state_texture_4 );
        this -> silver_trophy.setPosition( 
           this -> gold_trophy.getPosition().x, 
           this -> gold_trophy.getPosition().y * 1.3f
        );

        // Third award icon
        this -> bronze_trophy.setTexture( this -> state_texture_5 );
        this -> bronze_trophy.setPosition( 
           this -> gold_trophy.getPosition().x, 
           this -> silver_trophy.getPosition().y * 1.22f
        );

        // Drawing the images
        this -> game_window -> draw( background );
        this -> game_window -> draw( snake_branch_sprite );
        this -> game_window -> draw( gold_trophy );
        this -> game_window -> draw( silver_trophy );
        this -> game_window -> draw( bronze_trophy );
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
        this -> back_to_menu.setFillColor( this -> textColor );
        this -> back_to_menu.setPosition( 
            game_window_size_x * 0.03f, 
            game_window_size_y * 0.91f 
        );
        this -> back_to_menu.setCharacterSize( this -> text_size + 6 );

        // First award player name

        // Second award player name

        // Third award player name
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

        // First award player name settings

        // Second award player name settings

        // Third award player name settings

        // Draw stuff
        this -> game_window -> draw( this -> back_to_menu );
    }
}