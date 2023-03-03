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
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>

// STD
#include <fstream>
#include <algorithm>
#include <cstdint>
#include <filesystem>
#include <functional>
#include <map>
#include <new>
#include <string>
#include <utility>
#include <vector>

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
        game_window( game_window ),
        string_first( "" ),
        string_second( "" ),
        string_third( "" ){

        // Compute best scores
        this -> scores_map = this -> getScoresMap();

        // Draw widgets
        this -> drawWidgets();
    }

    //====================================================
    //     getScoresContainer
    //====================================================
    /**
     * @brief Method used to get the scores container with also player names.
     * 
     */
    std::multimap<uint64_t, std::string, std::greater<int64_t>> ScoresState::getScoresMap(){

        // Read scores from file
        std::ifstream score_file( this -> game_window -> score_file_path );
        if( ! score_file ){
            std::ofstream default_settings( this -> game_window -> score_file_path );
            default_settings.close();
        }
        std::string score_line;
        std::vector<std::string> lines;
        while( std::getline( score_file, score_line ) ){
            lines.push_back( score_line );
        }

        // Compute best score
        std::multimap <uint64_t, std::string, std::greater<int64_t>> scores_map;
        std::string player_name;
        uint64_t player_score;
        for( const auto& line: lines ){
            std::stringstream words( line );
            words >> player_score >> player_name;
            scores_map.insert( { player_score, player_name } );
        }

        // Close stream
        score_file.close();

        return scores_map;
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
        if( ! state_texture_3.loadFromFile( "img/textures/gold_icon.png" ) ){
            this -> game_window -> close();
        }
        if( ! state_texture_4.loadFromFile( "img/textures/silver_icon.png" ) ){
            this -> game_window -> close();
        }
        if( ! state_texture_5.loadFromFile( "img/textures/bronze_icon.png" ) ){
            this -> game_window -> close();
        }
        if( ! state_texture_6.loadFromFile( "img/images/scores_title.png" ) ){
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

        // Title image
        this -> title.setTexture( this -> state_texture_6 );
        this -> title.setPosition( 
           ( this -> game_window_size_x * 0.5f - this -> title.getGlobalBounds().width * 0.5f ), 
           ( this -> game_window_size_y * 0.5f - this -> title.getGlobalBounds().height * 0.5f ) * 0.2f
        );

        // First award icon
        this -> gold_trophy.setTexture( this -> state_texture_3 );
        this -> gold_trophy.setPosition( 
           ( this -> game_window_size_x * 0.5f - this -> title.getGlobalBounds().width * 0.5f ), 
           ( this -> game_window_size_y * 0.5f - this -> gold_trophy.getGlobalBounds().height * 0.5f )
        );

        // Second award icon
        this -> silver_trophy.setTexture( this -> state_texture_4 );
        this -> silver_trophy.setPosition( 
           this -> gold_trophy.getPosition().x * 1.023f, 
           this -> gold_trophy.getPosition().y * 1.35f
        );

        // Third award icon
        this -> bronze_trophy.setTexture( this -> state_texture_5 );
        this -> bronze_trophy.setPosition( 
           this -> silver_trophy.getPosition().x, 
           this -> silver_trophy.getPosition().y * 1.225f
        );

        // Drawing the images
        this -> game_window -> draw( background );
        this -> game_window -> draw( snake_branch_sprite );
        this -> game_window -> draw( gold_trophy );
        this -> game_window -> draw( silver_trophy );
        this -> game_window -> draw( bronze_trophy );
        this -> game_window -> draw( title );
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
        this -> first_player.setFillColor( this -> textColor );
        this -> first_player.setPosition( 
            ( this -> game_window_size_x * 0.5f - this -> title.getGlobalBounds().width * 0.5f ) * 0.95f,
            ( this -> game_window_size_y * 0.5f - this -> title.getGlobalBounds().height * 0.5f ) * 0.94f
        );
        this -> first_player.setCharacterSize( this -> text_size + 20 );

        // Second award player name
        this -> second_player.setFillColor( this -> textColor );
        this -> second_player.setPosition( 
            ( this -> game_window_size_x * 0.5f - this -> title.getGlobalBounds().width * 0.5f ) * 0.95f,
            ( this -> game_window_size_y * 0.5f - this -> title.getGlobalBounds().height * 0.5f ) * 1.22f
        );
        this -> second_player.setCharacterSize( this -> text_size + 20 );

        // Third award player name
        this -> third_player.setFillColor( this -> textColor );
        this -> third_player.setPosition( 
            ( this -> game_window_size_x * 0.5f - this -> title.getGlobalBounds().width * 0.5f ) * 0.95f,
            ( this -> game_window_size_y * 0.5f - this -> title.getGlobalBounds().height * 0.5f ) * 1.49f
        );
        this -> third_player.setCharacterSize( this -> text_size + 20 );
    }

    //====================================================
    //     initStrings
    //====================================================
    /**
     * @brief Method used to initialize scores strings.
     * 
     */
    void ScoresState::initStrings(){
        try{
            this -> iterator = this -> scores_map.begin();
            this -> string_first = std::to_string( iterator -> first ) + "   " + iterator -> second;
            try{
                this -> iterator++;
                this -> string_second = std::to_string( iterator -> first ) + "   " + iterator -> second;
                try{
                    this -> iterator++;
                    this -> string_third = std::to_string( iterator -> first ) + "   " + iterator -> second;
                }
                catch( const std::bad_alloc& ){
                    this -> string_third = "Empty";
                }
            }
            catch( const std::bad_alloc& ){
                this -> string_second = "Empty";
                this -> string_third = "Empty";
            }
        }
        catch( const std::bad_alloc& ){
            this -> string_first = "Empty";
            this -> string_second = "Empty";
            this -> string_third = "Empty";
        }
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

        // Modify strings
        this -> initStrings();

        // First award player name settings
        this -> first_player.setFont( this -> font );
        this -> first_player.setString( this -> string_first );

        // Second award player name settings
        this -> second_player.setFont( this -> font );
        this -> second_player.setString( this -> string_second );

        // Third award player name settings
        this -> third_player.setFont( this -> font );
        this -> third_player.setString( this -> string_third );

        // Draw stuff
        this -> game_window -> draw( this -> back_to_menu );
        this -> game_window -> draw( this -> first_player );
        this -> game_window -> draw( this -> second_player );
        this -> game_window -> draw( this -> third_player );
    }
}