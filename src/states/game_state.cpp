//====================================================
//     File data
//====================================================
/**
 * @file game_state.cpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2022-12-25
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
#include <windows/pause_window.hpp>

// States
#include <states/game_state.hpp>
#include <states/state.hpp>

// Entities
#include <entities/snake.hpp>
#include <entities/food.hpp>

// Debug
#ifdef DEBUG_SNAKE_GAME
    #include <ptc/print.hpp>
#endif

// SFML
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp> 
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/System/Vector2.hpp> 
#include <SFML/Audio/Sound.hpp>
#include <SFML/Audio/SoundBuffer.hpp>

// STD
#include <memory>
#include <string>
#include <algorithm>
#include <string_view> 
#include <vector> 
#include <fstream>
#include <filesystem>

namespace snake::state{

    //====================================================
    //     Static variables
    //====================================================
    sf::SoundBuffer GameState::state_sound_1;
    sf::SoundBuffer GameState::state_sound_2;

    //====================================================
    //     GameState (constructor)
    //====================================================
    /**
     * @brief Main constructor of the Game class.
     * 
     * @param game_window The window to which the state is drawn.
     */
    GameState::GameState( window::GameWindow* game_window ): 
        game_window( game_window ),
        background_file( "img/images/game_background.jpg" ){

        // Set snake head and texture properties
        this -> state_texture_1.loadFromFile( "img/textures/snake_head.png" );;
        this -> snake -> head.setTexture( this -> state_texture_1 );
        this -> snake -> head.setOrigin( ( sf::Vector2f )this -> state_texture_1.getSize() / 2.f );
        this -> snake -> relHeadPos( 0, - this -> snake -> body[0].getSize().y );

        // Set food texture properties
        this -> state_texture_2.loadFromFile( "img/textures/food.png" );
        this -> food -> food.setTexture( this -> state_texture_2 );

        // Default move up
        this -> snake -> moveSmoothly( 0.f, - this -> snake -> speedV );

        // Change background
        this -> process_background = this -> game_window -> processInputFile( 
            std::ifstream( this -> game_window -> options_file_path ), 2, 1 
        );
        if( this -> process_background != "default" ){
            this -> background_file = this -> process_background;
        }

        // Save player name
        this -> player_name = this -> game_window -> processInputFile(
            std::ifstream( this -> game_window -> options_file_path ), 0, 1
        );

        // Get best score
        if( this -> game_window -> scores_container.size() == 0 ){
            this -> best_score = 0;
        }
        else{
            this -> best_score = *max_element( 
                this -> game_window -> scores_container.begin(), 
                this -> game_window -> scores_container.end() 
            );
        }

        // Load sounds
        this -> loadSounds();

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
    void GameState::drawState() {

        // Clear the window
        this -> game_window -> clear( this -> background_color );

        // Drawing and updating entities
        this -> packWidgets();
        this -> drawEntities();
        this -> updateEntities();
        this -> gameRules();
        
        // Display the state
        this -> game_window -> setFramerateLimit( 15 );
        this -> game_window -> display();
    }

    //====================================================
    //     drawEntities
    //====================================================
    /**
     * @brief Method used to draw the state entities.
     * 
     */
    void GameState::drawEntities() const {
        this -> snake -> draw();
        this -> food -> draw();
    }

    //====================================================
    //     updateEntities
    //====================================================
    /**
     * @brief Method used to update the state entities.
     * 
     */
    void GameState::updateEntities() {
        this -> snake -> update();
    }

    //====================================================
    //     gameOver
    //====================================================
    /**
     * @brief Method used to set the game over condition.
     * 
     */
    void GameState::gameOver(){

        // Kill snake
        this -> snake_looses.play();
        this -> snake -> death();

        // Append score to the score file
        std::ofstream score_file( this -> game_window -> score_file_path, std::ios::app );
        if( ! score_file ){
            std::ofstream default_settings( this -> game_window -> score_file_path );
            default_settings.close();
        }
        score_file << this -> score << " " << this -> player_name << "\n";
        score_file.close();

        // Return to menu or quit game
        auto pause_window{ snake::window::PauseWindow( "GameOver" ) };
        if( pause_window.quit_game == true ) {
            this -> game_window -> close();
        }
        if( pause_window.back_to_menu == true ) {
            this -> game_window -> close();
            auto game_window{ snake::window::GameWindow() };
        }
    }

    //====================================================
    //     gameRules
    //====================================================
    /**
     * @brief Method used to set the game rules.
     * 
     */
    void GameState::gameRules(){

        // Check for collisions among snake head and food
        const sf::FloatRect head_bounding{ this -> snake -> head.getGlobalBounds() };
        const sf::FloatRect food_bounding{ this -> food -> food.getGlobalBounds() };
        if( head_bounding.intersects( food_bounding ) ){
            this -> snake_eat.play();
            this -> food -> respawn();
            this -> snake -> bodyGrow();
            this -> score += 1;
        }

        // Check for collisions among snake and the window border
        const auto snake_x_pos = this -> snake -> head.getPosition().x;
        const auto snake_y_pos = this -> snake -> head.getPosition().y;
        if( snake_x_pos >= window_x_max + window_x_max * 0.01 || snake_x_pos <= 0 - window_x_max * 0.01 || snake_y_pos >= window_y_max + window_y_max * 0.01 || snake_y_pos <= horizontal_line_y_coord - window_y_max * 0.01 ){
            this -> gameOver();
        }

        // Check for collision among snake and its body
        std::for_each( 
            this -> snake -> body.begin() + 1, 
            this -> snake -> body.end(), 
            [ &head_bounding, this ]( auto& elem ) {
                const sf::FloatRect body_bounding{ elem.getGlobalBounds() };
                if( head_bounding.intersects( body_bounding ) ){
                    this -> gameOver();
                }
            }
        );
    }

    //====================================================
    //     drawWidgets
    //====================================================
    /**
     * @brief Method used to draw widgets on the current state.
     * 
     */
    void GameState::drawWidgets(){

        // Score icon
        this -> score_icon.setTexture( this -> state_texture_2 );
        this -> score_icon.setPosition( 
            window_x_max * 0.02f, 
            window_y_max * 0.013f 
        );

        // Score text
        this -> score_update.setFillColor( sf::Color::Black );
        this -> score_update.setPosition( 
            window_x_max * 0.02f + this -> score_icon.getPosition().x * 1.4f, 
            window_y_max * 0.02f
        );
        this -> score_update.setCharacterSize( this -> text_size + 6 );

        // Best score icon
        this -> state_texture_6.loadFromFile( "img/textures/best_score.png" );
        this -> best_score_icon.setTexture( this -> state_texture_6 );
        this -> best_score_icon.setPosition( 
            window_x_max * 0.02f + this -> score_update.getPosition().x * 2.0f, 
            window_y_max * 0.015f
        );

        // Best score text
        this -> best_score_text.setFillColor( sf::Color::Black );
        this -> best_score_text.setPosition( 
            window_x_max * 0.02f + this -> best_score_icon.getPosition().x * 1.06f, 
            window_y_max * 0.02f
        );
        this -> best_score_text.setCharacterSize( this -> text_size + 6 );

        // Current player icon
        this -> state_texture_7.loadFromFile( "img/textures/player_icon.png" );
        this -> player_icon.setTexture( this -> state_texture_7 );
        this -> player_icon.setPosition( 
            window_x_max * 0.02f + this -> best_score_text.getPosition().x * 1.5f, 
            window_y_max * 0.02f
        );

        // Current player text
        this -> current_player_text.setFillColor( sf::Color::Black );
        this -> current_player_text.setPosition( 
            window_x_max * 0.02f + this -> player_icon.getPosition().x * 1.04f, 
            window_y_max * 0.02f
        );
        this -> current_player_text.setCharacterSize( this -> text_size + 6 );

        // Horizontal line
        this -> horizontal_line[0].position = sf::Vector2f( 0, this -> horizontal_line_y_coord );
        this -> horizontal_line[0].color = sf::Color::Black;
        this -> horizontal_line[1].position = sf::Vector2f( window_x_max, this -> horizontal_line_y_coord );
        this -> horizontal_line[1].color = sf::Color::Black;

        // Background
        if( ! this -> state_texture_3.loadFromFile( this -> background_file ) ){
            this -> game_window -> close();
        }
        this -> background.setSize( 
            sf::Vector2f( 
                window_x_max, 
                window_y_max
            )
        );
        this -> background.setTexture( &state_texture_3, true );

        // Title background
        if( ! this -> state_texture_4.loadFromFile( "img/images/title_game_background.jpg" ) ){
            this -> game_window -> close();
        }
        this -> title_background.setSize( 
            sf::Vector2f( 
                window_x_max, 
                this -> horizontal_line_y_coord
            )
        );
        this -> title_background.setTexture( &state_texture_4, true );
    }

    //====================================================
    //     packWidgets
    //====================================================
    /**
     * @brief Method used to update widgets on the current state.
     * 
     */
    void GameState::packWidgets(){

        // Score text settings
        this -> score_update.setFont( this -> font );
        this -> score_update.setString( std::to_string( this -> score ) );

        // Best score text settings
        this -> best_score_text.setFont( this -> font );
        this -> best_score_text.setString( std::to_string( this -> best_score ) );

        // Current player text settings
        this -> current_player_text.setFont( this -> font );
        this -> current_player_text.setString( this -> player_name );

        // Draw stuff
        this -> game_window -> draw( this -> background );
        this -> game_window -> draw( this -> title_background );
        this -> game_window -> draw( this -> score_update );
        this -> game_window -> draw( this -> best_score_text );
        this -> game_window -> draw( this -> score_icon );
        this -> game_window -> draw( this -> best_score_icon );
        this -> game_window -> draw( this -> horizontal_line, 2, sf::Lines );
        this -> game_window -> draw( this -> current_player_text );
        this -> game_window -> draw( this -> player_icon );
    }

    //====================================================
    //     loadSounds
    //====================================================
    /**
     * @brief Method to load sounds in the current state.
     * 
     */
    void GameState::loadSounds(){

        // Snake eat
        this -> state_sound_1.loadFromFile( "sounds/effects/snake_eat.wav" );
        this -> snake_eat.setBuffer( this -> state_sound_1 );

        // Snake looses
        this -> state_sound_2.loadFromFile( "sounds/effects/snake_looses.wav" );
        this -> snake_looses.setBuffer( this -> state_sound_2 );
    }
}