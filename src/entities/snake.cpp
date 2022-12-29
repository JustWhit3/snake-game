//====================================================
//     File data
//====================================================
/**
 * @file snake.cpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2022-12-27
 * @copyright Copyright (c) 2022 Gianluca Bianco under the MIT license.
 */

//====================================================
//     Headers
//====================================================

// Windows
#include <windows/game_window.hpp>

// Entities
#include <entities/snake.hpp>

// SFML
#include <SFML/Graphics/Color.hpp> 
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp> 

namespace snake::entity{

    //====================================================
    //     Snake (constructor)
    //====================================================
    /**
     * @brief Constructor of the snake class.
     * 
     */
    Snake::Snake( window::GameWindow* game_window ): Entity( game_window ){

        // Snake body shape settings
        this -> body.setSize( sf::Vector2f( 25.0f, 25.0f ) );
        this -> body.setFillColor( sf::Color( 76, 153, 0 ) );
        this -> body.setOutlineColor( sf::Color::Black );
        this -> body.setOutlineThickness( 2 );
        this -> body.setPosition( 530.f, 900.f );
    }

    //====================================================
    //     moveSmoothly
    //====================================================
    /**
     * @brief Method used to smoothly move an entity.
     * 
     * @param dt Delta time.
     * @param dir_x X position.
     * @param dir_y Y position.
     */
    void Snake::moveSmoothly( const float dir_x, const float dir_y ){

        // Save directions
        this -> direction_x = dir_x;
        this -> direction_y = dir_y;

        // Move
        this -> body.move( dir_x, dir_y );
        this -> head.move( dir_x, dir_y );
    }

    //====================================================
    //     update
    //====================================================
    /**
     * @brief Method used to update the entity movement.
     * 
     */
    void Snake::update(){

        // Default movement
        if( this -> direction_y < 0 ){
            this -> moveSmoothly( 0.f, - this -> speedV );
        }
        else if( this -> direction_y > 0 ){
            this -> moveSmoothly( 0.f, this -> speedV );
        }
        else if( this -> direction_x < 0 ){
            this -> moveSmoothly( 0.f, 0.f );
            this -> moveSmoothly( - this -> speedV, 0.f );
        }
        else if( this -> direction_x > 0 ){
            this -> moveSmoothly( 0.f, 0.f );
            this -> moveSmoothly( this -> speedV, 0.f );
        }

        // Key pressed changing direction
        if( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) ){
            this -> moveSmoothly( 0.f, - this -> speedV );
        }
        else if( sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) ){
            this -> moveSmoothly( 0.f, this -> speedV );
        }
        else if( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) ){
            this -> moveSmoothly( this -> speedV, 0.f );
        }
        else if( sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) ){
            this -> moveSmoothly( - this -> speedV, 0.f );
        }
    }

    //====================================================
    //     draw
    //====================================================
    /**
     * @brief Method used to draw the entity.
     * 
     */
    void Snake::draw() const {
        this -> game_window -> draw( this -> body );
        this -> game_window -> draw( this -> head );
    }
}