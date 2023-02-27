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
                    const sf::Color& idleColor, const sf::Color& hoverColor, const sf::Color& activeColor ):
        Widget( x, y, width, height, font, text, idleColor, hoverColor, activeColor ),
        has_been_pressed( false ),
        saved_text( "" ){
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
        this -> widgetState = WDGT_IDLE;

        // Mouse clicked
        if( this -> shape.getGlobalBounds().contains( mousePos ) ){
            this -> widgetState = WDGT_HOVER;

            if( sf::Mouse::isButtonPressed( sf::Mouse::Left ) ){
                this -> widgetState = WDGT_ACTIVE;
                this -> has_been_pressed = true;
            }
        }
        else{
            if( sf::Mouse::isButtonPressed( sf::Mouse::Left ) ){
                this -> widgetState = WDGT_IDLE;
                this -> has_been_pressed = false;
            }
        }

        if( this -> has_been_pressed == true ){
            this -> widgetState = WDGT_ACTIVE;
        }

        // Switch cases for textbox states
        switch( this -> widgetState ){
            case WDGT_IDLE:
                this -> shape.setFillColor( this -> idleColor );
                break;

            case WDGT_HOVER:
                this -> shape.setFillColor( this -> hoverColor );
                break;

            case WDGT_ACTIVE:
                this -> shape.setFillColor( this -> activeColor );
                if( sf::Keyboard::isKeyPressed( sf::Keyboard::Return ) ){
                    this -> saved_text = this -> text.getString();
                }
                break;

            default:
                this -> shape.setFillColor( sf::Color::Red );
                break;
        }
    }

    //====================================================
    //     updateText
    //====================================================
    /**
     * @brief Method used to update the text of the textbox.
     * 
     * @param event The event of the window in which the textbox is drawn.
     */
    void Textbox::updateText( const sf::Event& event ){
        if( event.type == sf::Event::TextEntered ){
            if( this -> widgetState == WDGT_ACTIVE ){
                switch( event.text.unicode ){

                    // Delete case
                    case '\b':{ 
                        this -> current_text = this -> text.getString();
                        if( this -> current_text.size() > 0 ){
                            this -> text.setString( 
                                current_text.erase( current_text.size() - 1, 1 ) 
                            );
                        }
                        break;
                    }

                    // Other cases
                    default:{
                        this -> input += event.text.unicode;
                        this -> input_text.setString( this -> input );
                        this -> text.setString( this -> input_text.getString() );
                        break;
                    }
                }
            }
        }
    }
}