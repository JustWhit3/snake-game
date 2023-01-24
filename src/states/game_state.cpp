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

// States
#include <states/game_state.hpp>
#include <states/loose_state.hpp>

// Entities
#include <entities/snake.hpp>
#include <entities/food.hpp>

// Debug
#ifdef DEBUG_SNAKE_GAME
    #include <ptc/print.hpp>
#endif

// Utility
#include <utility/gui.hpp>

// SFML
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp> 
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp> 

// STD
#include <memory>
#include <string>

namespace snake::state{

    //====================================================
    //     GameState (constructor)
    //====================================================
    /**
     * @brief Main constructor of the Game class.
     * 
     * @param game_window The window to which the state is drawn.
     */
    GameState::GameState( window::GameWindow* game_window ): 
        game_window( game_window ){

        // Set snake head and texture properties
        this -> state_texture_1.loadFromFile( "img/snake_head.png" );;
        this -> snake -> head.setTexture( this -> state_texture_1 );
        this -> snake -> head.setOrigin( ( sf::Vector2f )this -> state_texture_1.getSize() / 2.f );
        this -> snake -> relHeadPos( 0, - this -> snake -> body[0].getSize().y );

        // Default move up
        this -> snake -> moveSmoothly( 0.f, - this -> snake -> speedV );

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
        this -> drawEntities();
        this -> updateEntities();
        this -> packWidgets();
        this -> gameRules();
        
        // Display the state
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
        this -> snake -> death();
        this -> game_window -> states.insert( 
            { "Loose", std::make_shared<state::LooseState>( state::LooseState( game_window ) ) }
        );
        this -> game_window -> states.at( "Loose" ) -> drawState();
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
            this -> food -> respawn();
            this -> snake -> bodyGrow();
            this -> score += 1;
        }

        // Check for collisions among snake and the window border
        const auto window_x_max = this -> game_window -> getSize().x;
        const auto snake_x_pos = static_cast <unsigned int>( this -> snake -> head.getPosition().x );
        const auto window_y_max = this -> game_window -> getSize().y;
        const auto snake_y_pos = static_cast <unsigned int>( this -> snake -> head.getPosition().y );
        if( snake_x_pos >= window_x_max - 100 || snake_x_pos <= 0 || snake_y_pos >= window_y_max || snake_y_pos <= 0 ){
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

        // Score text
        this -> score_update.setFillColor( sf::Color::Black );
        this -> score_update.setPosition( 567.5f, 907.f );
        this -> score_update.setCharacterSize( 20 );
    }

    //====================================================
    //     packWidgets
    //====================================================
    /**
     * @brief Method used to update widgets on the current state.
     * 
     */
    void GameState::packWidgets(){
        this -> score_update.setFont( this -> font );
        this -> score_update.setString( std::to_string( this -> score ) );
        this -> game_window -> draw( this -> score_update );
    }
}