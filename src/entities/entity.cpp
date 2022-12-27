//====================================================
//     File data
//====================================================
/**
 * @file move.cpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2022-12-27
 * @copyright Copyright (c) 2022 Gianluca Bianco under the MIT license.
 */

//====================================================
//     Headers
//====================================================

// Entities
#include <entities/entity.hpp>

// SFML
#include <SFML/Graphics.hpp>


namespace snake::entity{

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
    void Entity::moveSmoothly( const float dt, const float dir_x, const float dir_y ){
        ( void ) dt;
        ( void ) dir_x;
        ( void ) dir_y;
    }

    //====================================================
    //     update
    //====================================================
    /**
     * @brief Method used to update the entity movement.
     * 
     * @param dt The delta time.
     */
    void Entity::update( const float dt ){
        ( void ) dt;
    }
}