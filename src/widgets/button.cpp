//====================================================
//     File data
//====================================================
/**
 * @file button.cpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2022-12-22
 * @copyright Copyright (c) 2022 Gianluca Bianco under the MIT license.
 */

//====================================================
//     Headers
//====================================================

// Windows
#include <windows/game.hpp>

// Widgets
#include <widgets/button.hpp>

// STD
#include <functional>

namespace snake::widget{

    //====================================================
    //     Button (constructor)
    //====================================================
    /**
     * @brief Main constructor of the button class.
     * 
     * @param x X position of the button.
     * @param y Y position of the button.
     * @param width Button width.
     * @param height Button height.
     * @param font Button text font.
     * @param text Button text
     * @param idleColor Default color of the button.
     * @param hoverColor Button color when passing with mouse.
     * @param activeColor Button color when clicking
     */
    Button::Button( float x, float y, float width, float height, sf::Font font, 
                    std::string text, sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor ):
        buttonState( BTN_IDLE ),
        font( font ),
        idleColor( idleColor ),
        hoverColor( hoverColor ),
        activeColor( activeColor ),
        action( []{} ){

        // Setting button shape
        this -> shape.setPosition( sf::Vector2f( x, y ) );
        this -> shape.setSize( sf::Vector2f( width, height ) );

        // Setting button text properties
        this -> text.setFont( this -> font );
        this -> text.setString( text );
        this -> text.setFillColor( sf::Color::Black );
        this -> text.setCharacterSize( 12 );

        // Centering the button
        this -> centering();

        // Coloring button
        this -> shape.setFillColor( this -> idleColor );
    }

    //====================================================
    //     render
    //====================================================
    /**
     * @brief Method used for button rendering.
     * 
     * @param target The target to draw button.
     */
    void Button::render( window::GameWindow* target ) const {
        target -> draw( this -> shape );
        target -> draw( this -> text );
    }

    //====================================================
    //     update
    //====================================================
    /**
     * @brief Method used to update the booleans for hover and pressed.
     * 
     * @param mouse_pos The mouse position.
     */
    void Button::update( const sf::Vector2f mousePos ){

        // Idle
        this -> buttonState = BTN_IDLE;

        // Hover
        if( this -> shape.getGlobalBounds().contains( mousePos ) ){
            this -> buttonState = BTN_HOVER;

            // Pressed
            if( sf::Mouse::isButtonPressed( sf::Mouse::Left ) ){
                this -> buttonState = BTN_ACTIVE;
            }
        }

        // Switch cases for button states
        switch( this -> buttonState ){
            case BTN_IDLE:
                this -> shape.setFillColor( this -> idleColor );
                break;

            case BTN_HOVER:
                this -> shape.setFillColor( this -> hoverColor );
                break;

            case BTN_ACTIVE:
                this -> shape.setFillColor( this -> activeColor );
                this -> action();
                break;

            default:
                this -> shape.setFillColor( sf::Color::Red );
                break;
        }
    }

    //====================================================
    //     isPressed
    //====================================================
    /**
     * @brief Method used to define button pressed state.
     * 
     * @return true If button is pressed.
     * @return false Otherwise.
     */
    constexpr bool Button::isPressed() const{
        if( this -> buttonState == BTN_ACTIVE ){
            return true;
        }
        return false;
    }

    //====================================================
    //     pack
    //====================================================
    /**
     * @brief Method used to draw the button in the target.
     * 
     * @param target The target to which the button is drawn in.
     */
    void Button::pack( window::GameWindow* target ){
        this -> update( target -> mapPixelToCoords( sf::Mouse::getPosition( *target ) ) );
        this -> render( target );
    }

    //====================================================
    //     centering
    //====================================================
    /**
     * @brief Method used to center the text position into the button shape.
     * 
     */
    void Button::centering(){
        this -> text.setPosition(
            this -> shape.getPosition().x + ( this -> shape.getGlobalBounds().width / 2.f ) - ( this -> text.getGlobalBounds().width / 2.f ),
            this -> shape.getPosition().y + ( this -> shape.getGlobalBounds().height / 2.f ) - ( this -> text.getGlobalBounds().height / 2.f ) - this -> text.getCharacterSize() / 4
        );
    }

    //====================================================
    //     setTextSize
    //====================================================
    /**
     * @brief Method used to set the button text size.
     * 
     * @param size The new size to be set.
     */
    void Button::setTextSize( int32_t size ){
        this -> text.setCharacterSize( size );
        this -> centering();
    }

    //====================================================
    //     setAction
    //====================================================
    /**
     * @brief Function used to set an action which is performed by the button when pressed.
     * 
     * @param action The function which should be ran by the button when pressed.
     */
    void Button::setAction( std::function<void()> action ){
        this -> action = action;
    }

}
