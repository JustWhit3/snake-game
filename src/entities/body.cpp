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
    Body::Body(){
        this -> setSize( sf::Vector2f( 25.0f, 25.0f ) );
        this -> setFillColor( sf::Color::Green );
        this -> setOutlineColor( sf::Color::Black );
        this -> setOutlineThickness( 2 );
        this -> setPosition( 530.f, 100.f );
    }
    
}