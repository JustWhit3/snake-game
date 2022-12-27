//====================================================
//     File data
//====================================================
/**
 * @file body.cpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2022-12-27
 * @copyright Copyright (c) 2022 Gianluca Bianco under the MIT license.
 */

//====================================================
//     Headers
//====================================================

// Entities
#include <entities/body.hpp>

// SFML
#include <SFML/Graphics.hpp>

namespace snake::entity{

    //====================================================
    //     Body (constructor)
    //====================================================
    /**
     * @brief Constructor of the body class.
     * 
     */
    Body::Body(){

        // Shape settings
        this -> setSize( sf::Vector2f( 25.0f, 25.0f ) );
        this -> setFillColor( sf::Color::Green );
        this -> setOutlineColor( sf::Color::Black );
        this -> setOutlineThickness( 2 );
        this -> setPosition( 530.f, 100.f );

        // Other settings
        this -> speed = 100;
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
    void Body::moveSmoothly( const float dt, const float dir_x, const float dir_y ){
        this -> move( dir_x * this -> speed * dt, dir_y * this -> speed * dt );
    }

    //====================================================
    //     update
    //====================================================
    /**
     * @brief Method used to update the entity movement.
     * 
     * @param dt The delta time.
     */
    void Body::update( const float dt ){

        constexpr float ds = 0.01f;

        if( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) ){
            this -> moveSmoothly( dt, 0.f, -ds );
        }
        else if( sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) ){
            this -> moveSmoothly( dt, 0.f, ds );
        }
        else if( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) ){
            this -> moveSmoothly( dt, ds, 0.f );
        }
        else if( sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) ){
            this -> moveSmoothly( dt, -ds, 0.f );
        }
    }
}