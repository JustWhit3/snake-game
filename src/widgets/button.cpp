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

// Widgets
#include <widgets/button.hpp>

// SFML
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp> 

// Debug
#ifdef DEBUG_SNAKE_GAME
    #include <ptc/print.hpp>
#endif

// STD
#include <functional>
#include <string>
#include <cstdint>

// Required by IWYU
namespace sf { 
    class Font;
}

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
    Button::Button( float x, float y, float width, float height, 
                    const sf::Font& font, const std::string& text, 
                    const sf::Color& idleColor, const sf::Color& hoverColor, const sf::Color& activeColor ):
        buttonState( BTN_IDLE ),
        font( font ),
        idleColor( idleColor ),
        hoverColor( hoverColor ),
        activeColor( activeColor ),
        action( []{} ),
        command_action( []{} ),
        focus( false ){

        // Setting button shape
        this -> shape.setPosition( sf::Vector2f( x, y ) );
        this -> shape.setSize( sf::Vector2f( width, height ) );
        this -> shape.setOutlineThickness( -5.f );
        this -> shape.setOutlineColor( sf::Color::Black );

        // Setting button text properties
        this -> text.setFont( this -> font );
        this -> text.setString( text );
        this -> text.setFillColor( sf::Color::Black );
        this -> text.setCharacterSize( 12 );

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
        if( this -> shape.getGlobalBounds().contains( mousePos ) || this -> focus == true ){
            this -> buttonState = BTN_HOVER;

            // Pressed
            if( sf::Mouse::isButtonPressed( sf::Mouse::Left ) || sf::Keyboard::isKeyPressed( sf::Keyboard::Return ) ){
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
        this -> centering();
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
    }

    //====================================================
    //     setAction
    //====================================================
    /**
     * @brief Function used to set an action which is performed by the button when pressed.
     * 
     * @param action The function which should be ran by the button when pressed.
     */
    void Button::setAction( const std::function<void()>& action ){
        this -> action = action;
    }

    //====================================================
    //     setOutlineColor
    //====================================================
    /**
     * @brief Method used to set the outline color of the button.
     * 
     * @param color The color to be set.
     */
    void Button::setOutlineColor( const sf::Color& color ){
        this -> shape.setOutlineColor( color );
    }

    //====================================================
    //     setOutlineThickness
    //====================================================
    /**
     * @brief Method used to set the outline thickness of the button.
     * 
     * @param thickness The outline thickness to be set.
     */
    void Button::setOutlineThickness( float thickness ){
        this -> shape.setOutlineThickness( - thickness );
    }

    //====================================================
    //     setFocus
    //====================================================
    /**
     * @brief Method used to move focus on the button.
     * 
     * @param focus The focus condition.
     */
    void Button::setFocus( const bool focus ){
        this -> focus = focus;
    }

    //====================================================
    //     map_btn
    //====================================================
    /**
     * @brief Function used to map two buttons.
     * 
     * @param btn The button to map with
     */
    void Button::map( std::shared_ptr<Button>& btn, const sf::Keyboard::Key& key ){
        if( sf::Keyboard::isKeyPressed( key ) && this -> focus ){
            btn -> focus = true;
            this -> focus = false;
        }
    }
}
