//====================================================
//     File data
//====================================================
/**
 * @file generic.hpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2022-12-29
 * @copyright Copyright (c) 2022 Gianluca Bianco under the MIT license.
 */

//====================================================
//     Preprocessor directives
//====================================================
#pragma once
#ifndef SNAKE_GAME_GENERIC_UTILITY
#define SNAKE_GAME_GENERIC_UTILITY

//====================================================
//     Headers
//====================================================

// STD
#include <random>

namespace snake::utility{

    //====================================================
    //     Preprocessor directives
    //====================================================
    /**
     * @brief Function used to generate random number in a range.
     * 
     * @tparam T The type of the random number range.
     * @param range_from The starting range value.
     * @param range_to The ending range value.
     * @return T The type of the return number.
     */
    template<typename T>
    T random( T range_from, T range_to ){

        // Initialize random number generator
        std::random_device rand_dev;
        std::mt19937 generator( rand_dev() );
        std::uniform_int_distribution<T> distr( range_from, range_to );

        // Return the random number
        return distr( generator );
    }
}

#endif