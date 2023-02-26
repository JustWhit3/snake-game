//====================================================
//     File data
//====================================================
/**
 * @file textbox.cpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2022-12-26
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

// Widgets
#include <widgets/textbox.hpp>

// Debug
#ifdef DEBUG_SNAKE_GAME
    #include <ptc/print.hpp>
#endif

// SFML
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp> 
#include <SFML/Window/Keyboard.hpp>

namespace snake::widget{

    //====================================================
    //     Textbox (constructor)
    //====================================================
    /**
     * @brief Main constructor of the textbox class.
     * 
     * @param x X position of the textbox.
     * @param y Y position of the textbox.
     * @param width textbox width.
     * @param height textbox height.
     * @param font textbox text font.
     * @param text textbox text
     */
    Textbox::Textbox( float x, float y, float width, float height, 
                    const sf::Font& font, const std::string& text,
                    const sf::Color& idleColor, const sf::Color& hoverColor ):
        font( font ),
        idleColor( idleColor ),
        hoverColor( hoverColor ),
        textboxState( TXBX_IDLE ),
        focus( false ){

        // Setting textbox shape
        this -> shape.setPosition( sf::Vector2f( x, y ) );
        this -> shape.setSize( sf::Vector2f( width, height ) );
        this -> shape.setOutlineThickness( -4.f );
        this -> shape.setOutlineColor( sf::Color::Black );

        // Setting textbox text properties
        this -> text.setFont( this -> font );
        this -> text.setString( text );
        this -> text.setCharacterSize( 12 );

        // Coloring textbox
        this -> shape.setFillColor( this -> idleColor );
    }

    //====================================================
    //     update
    //====================================================
    /**
     * @brief Method used to update the textbox status.
     * 
     * @param mouse_pos The mouse position.
     */
    void Textbox::update( const sf::Vector2f mousePos ){

        // Idle
        this -> textboxState = TXBX_IDLE;

        // Mouse clicked
        if( this -> shape.getGlobalBounds().contains( mousePos ) ){
            this -> textboxState = TXBX_HOVER;

            if( sf::Mouse::isButtonPressed( sf::Mouse::Left ) ){
                this -> textboxState = TXBX_ACTIVE;
                // do something...
            }
        }

        // Enter clicked
        else if( this -> focus == true ){
            this -> textboxState = TXBX_HOVER;

            if( sf::Keyboard::isKeyPressed( sf::Keyboard::Return ) ){
                this -> textboxState = TXBX_ACTIVE;
                // do something...
            }
        }

        // Switch cases for textbox states
        switch( this -> textboxState ){
            case TXBX_IDLE:
                this -> shape.setFillColor( this -> idleColor );
                break;

            case TXBX_HOVER:
                this -> shape.setFillColor( this -> hoverColor );
                break;

            case TXBX_ACTIVE:
            //  this -> action();
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
     * @brief Method used to define textbox pressed state.
     * 
     * @return true If textbox is pressed.
     * @return false Otherwise.
     */
    constexpr bool Textbox::isPressed() const{
        if( this -> textboxState == TXBX_ACTIVE ){
            return true;
        }
        return false;
    }

    //====================================================
    //     centering
    //====================================================
    /**
     * @brief Method used to center the text position into the textbox shape.
     * 
     */
    void Textbox::centering(){
        this -> text.setPosition(
            this -> shape.getPosition().x + ( this -> shape.getGlobalBounds().width / 2.f ) - ( this -> text.getGlobalBounds().width / 2.f ),
            this -> shape.getPosition().y + ( this -> shape.getGlobalBounds().height / 2.f ) - ( this -> text.getGlobalBounds().height / 2.f ) - this -> text.getCharacterSize() / 4
        );
    }

    //====================================================
    //     setTextSize
    //====================================================
    /**
     * @brief Method used to set the textbox text size.
     * 
     * @param size The new size to be set.
     */
    void Textbox::setTextSize( int32_t size ){
        this -> text.setCharacterSize( size );
    }

    //====================================================
    //     setOutlineColor
    //====================================================
    /**
     * @brief Method used to set the outline color of the textbox.
     * 
     * @param color The color to be set.
     */
    void Textbox::setOutlineColor( const sf::Color& color ){
        this -> shape.setOutlineColor( color );
    }

    //====================================================
    //     setOutlineThickness
    //====================================================
    /**
     * @brief Method used to set the outline thickness of the textbox.
     * 
     * @param thickness The outline thickness to be set.
     */
    void Textbox::setOutlineThickness( float thickness ){
        this -> shape.setOutlineThickness( - thickness );
    }

    //====================================================
    //     setTextColor
    //====================================================
    /**
     * @brief Method used to set the color of the textbox text.
     * 
     * @param color The new color to be set.
     */
    void Textbox::setTextColor( const sf::Color& color ){
        this -> text.setFillColor( color );
    }
}