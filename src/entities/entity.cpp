//====================================================
//     File data
//====================================================
/**
 * @file entity.cpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2022-12-29
 * @copyright Copyright (c) 2022 Gianluca Bianco under the MIT license.
 */

//====================================================
//     Headers
//====================================================

// Entities
#include <entities/entity.hpp>

namespace snake::entity{

    //====================================================
    //     Entity (constructor)
    //====================================================
    /**
     * @brief Main constructor of the entity class.
     * 
     * @param game_window THe window to which the entity is drawn into.
     */
    Entity::Entity( window::GameWindow* game_window ): game_window( game_window ){

    }

    //====================================================
    //     update
    //====================================================
    /**
     * @brief Method used to update an entity in each loop iteration.
     * 
     */
    void Entity::update(){

    }
}