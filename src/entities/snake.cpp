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

// Entities
#include <entities/entity.hpp>
#include <entities/snake.hpp>

// Debug
#ifdef DEBUG_SNAKE_GAME
    #include <ptc/print.hpp>
#endif

// SFML
#include <SFML/Graphics/Color.hpp> 
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Keyboard.hpp> 
#include <SFML/Graphics/RectangleShape.hpp> 
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Rect.hpp>

// STD
#include <algorithm>
#include <memory>
#include <vector>
#include <fstream>

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
        this -> body_shape.setSize( sf::Vector2f( this -> body_dimension, this -> body_dimension ) );
        this -> body_shape.setFillColor( sf::Color( 76, 153, 0 ) );
        this -> body_shape.setOutlineColor( sf::Color::Black );
        this -> body_shape.setOutlineThickness( 2 );
        this -> body_shape.setPosition( this -> game_window_size_x / 2.0f - head.getGlobalBounds().width * 2.0f, 900.f );
        this -> body_shape.setOrigin( ( sf::Vector2f )this -> body_shape.getSize() / 2.f );

        // Adding first body piece to snake
        this -> body.push_back( body_shape );

        // Change speed if option is set
        std::ifstream options_file( this -> game_window -> options_file_path );
        std::string input;
        std::vector<std::string> lines;
        while( std::getline( options_file, input ) ){
            lines.push_back( input );
        }
        std::string str1, str2;
        std::stringstream words( lines[1] );
        words >> str1 >> str2;
        this -> speedV = std::stoi( str2 );
        options_file.close();
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

        // Move snake
        this -> head.move( dir_x, dir_y );
        std::for_each(
            body.begin(), 
            body.end(), 
            [ &dir_x, &dir_y ]( auto& el ){ el.move( dir_x, dir_y ); } 
        );
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
        if( this -> direction_y < 0 ){ // UP
            if( this -> head.getRotation() == 270 ){
                this -> rotate( 90 );
            }
            else if( this -> head.getRotation() == 90 ){
                this -> rotate( -90 ); 
            }
            else if( this -> head.getRotation() == 180 ){
                this -> rotate( 180 ); 
            }
            this -> relHeadPos( 0, - this -> body[0].getSize().x );
            this -> moveSmoothly( 0.f, - this -> speedV );
            this -> setGrowPosition( 0, this -> body_dimension );
        }
        else if( this -> direction_y > 0 ){ // DOWN
            if( this -> head.getRotation() == 270 ){
                this -> rotate( -90 );
            }
            else if( this -> head.getRotation() == 90 ){
                this -> rotate( 90 ); 
            }
            else if( this -> head.getRotation() == 0 ){
                this -> rotate( 180 ); 
            }
            this -> relHeadPos( 0, this -> body[0].getSize().x );
            this -> moveSmoothly( 0.f, this -> speedV );
            this -> setGrowPosition( 0, -this -> body_dimension );
        }
        else if( this -> direction_x < 0 ){ // LEFT
            if( this -> head.getRotation() == 0 ){
                this -> rotate( -90 ); 
            }
            else if( this -> head.getRotation() == 180 ){
                this -> rotate( 90 );
            }
            else if( this -> head.getRotation() == 90 ){
                this -> rotate( 180 ); 
            }
            this -> relHeadPos( - this -> body[0].getSize().x, 0 );
            this -> moveSmoothly( 0.f, 0.f );
            this -> moveSmoothly( - this -> speedV, 0.f );
            this -> setGrowPosition( this -> body_dimension, 0 );
        }
        else if( this -> direction_x > 0 ){ // RIGHT
            if( this -> head.getRotation() == 0 ){
                this -> rotate( 90 );   
            }
            else if( this -> head.getRotation() == 180 ){
                this -> rotate( -90 );   
            }
            else if( this -> head.getRotation() == 270 ){
                this -> rotate( 180 ); 
            }
            this -> relHeadPos( this -> body[0].getSize().x, 0 );
            this -> moveSmoothly( 0.f, 0.f );
            this -> moveSmoothly( this -> speedV, 0.f );
            this -> setGrowPosition( -this -> body_dimension, 0 );
        }

        // Key pressed changing direction
        if( sf::Keyboard::isKeyPressed( sf::Keyboard::Up ) ){
            this -> moveSmoothly( 0.f, - this -> infinitesimal_speedV );
        }
        else if( sf::Keyboard::isKeyPressed( sf::Keyboard::Down ) ){
            this -> moveSmoothly( 0.f, this -> infinitesimal_speedV );
        }
        else if( sf::Keyboard::isKeyPressed( sf::Keyboard::Right ) ){
            this -> moveSmoothly( this -> infinitesimal_speedV, 0.f );
        }
        else if( sf::Keyboard::isKeyPressed( sf::Keyboard::Left ) ){
            this -> moveSmoothly( - this -> infinitesimal_speedV, 0.f );
        }
    }

    //====================================================
    //     setGrowPosition
    //====================================================
    /**
     * @brief Method used to set the grow position.
     * 
     * @param x Increment of x position.
     * @param y Increment of y position.
     */
    void Snake::setGrowPosition( float x, float y ){
        if( body.size() > 1 ){
            for( auto i = body.size() - 1; i > 0; i-- ){
                this -> body[i].setPosition( 
                    this -> body[i-1].getPosition().x + x, 
                    this -> body[i-1].getPosition().y + y 
                );
            }
        }   
    }

    //====================================================
    //     draw
    //====================================================
    /**
     * @brief Method used to draw the snake entity.
     * 
     */
    void Snake::draw() const {
        std::for_each(
            this -> body.cbegin(),
            this -> body.cend(),
            [ this ]( const auto& el ){ this -> game_window -> draw( el ); }
        );
        this -> game_window -> draw( this -> head );
    }

    //====================================================
    //     bodyGrow
    //====================================================
    /**
     * @brief Method used to grow the snake body when food is ate.
     * 
     */
    void Snake::bodyGrow(){
        auto body_piece = this -> body_shape;
            if( this -> direction_y < 0 )
                body_piece.setPosition( 
                    this -> body[ body.size() - 1 ].getPosition().x, 
                    this -> body[ body.size() - 1 ].getPosition().y + this -> body_dimension
                );
            else if( this -> direction_y > 0 )
                body_piece.setPosition( 
                    this -> body[ body.size() - 1 ].getPosition().x, 
                    this -> body[ body.size() - 1 ].getPosition().y - this -> body_dimension
                );
            else if( this -> direction_x < 0 )
                body_piece.setPosition( 
                    this -> body[ body.size() - 1 ].getPosition().x + this -> body_dimension, 
                    this -> body[ body.size() - 1 ].getPosition().y
                );
            else if( this -> direction_x > 0 )
                body_piece.setPosition( 
                    this -> body[ body.size() - 1 ].getPosition().x - this -> body_dimension, 
                    this -> body[ body.size() - 1 ].getPosition().y
                );
        body_piece.setOrigin( this -> body[ body.size() - 1 ].getOrigin() );
        this -> body.push_back( body_piece );
    }

    //====================================================
    //     relHeadPos
    //====================================================
    /**
     * @brief Method used to correct the head position with respect to the body one.
     * 
     * @param x The increment for the x position.
     * @param y The increment for the y position.
     */
    void Snake::relHeadPos( float x, float y ){
        this -> head.setPosition(
            this -> body[0].getPosition().x + x,
            this -> body[0].getPosition().y + y
        );
    }

    //====================================================
    //     death
    //====================================================
    /**
     * @brief Method used to deal with snake death.
     * 
     */
    void Snake::death(){
        this -> speedV = 0;
    }

    //====================================================
    //     rotate
    //====================================================
    /**
     * @brief Method used to rotate snake.
     * 
     * @param angle Rotation angle.
     */
    void Snake::rotate( float angle ){
        this -> head.rotate( angle ); 
    }
}