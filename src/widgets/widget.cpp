//====================================================
//     File data
//====================================================
/**
 * @file state.cpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2022-12-26
 * @copyright Copyright (c) 2022 Gianluca Bianco under the MIT license.
 */

//====================================================
//     Headers
//====================================================

// Widgets
#include <widgets/widget.hpp>

namespace snake::widget{

    //====================================================
    //     Widget (constructor)
    //====================================================
    /**
     * @brief Default constructor of the widget class.
     * 
     * @param x X position of the Widget.
     * @param y Y position of the Widget.
     * @param width Widget width.
     * @param height Widget height.
     * @param font Widget text font.
     * @param text Widget text
     * @param idleColor Default color of the Widget.
     * @param hoverColor Widget color when passing with mouse.
     * @param activeColor Widget color when clicking
     */
    Widget::Widget( float x, float y, float width, float height, 
                    const sf::Font& font, const std::string& text, 
                    const sf::Color& idleColor, const sf::Color& hoverColor, const sf::Color& activeColor ): 
        focus( false ),        
        font( font ),
        idleColor( idleColor ),
        hoverColor( hoverColor ),
        activeColor( activeColor ),
        widgetState( WDGT_IDLE ){

        // Setting Widget shape
        this -> shape.setPosition( sf::Vector2f( x, y ) );
        this -> shape.setSize( sf::Vector2f( width, height ) );
        this -> shape.setOutlineThickness( -4.f );
        this -> shape.setOutlineColor( sf::Color::Black );

        // Setting Widget text properties
        this -> text.setFont( this -> font );
        this -> text.setString( text );
        this -> text.setCharacterSize( 12 );

        // Coloring Widget
        this -> shape.setFillColor( this -> idleColor );
    }

    //====================================================
    //     centering
    //====================================================
    /**
     * @brief Method used to center the text position into the shape.
     * 
     */
    void Widget::centering(){
        this -> text.setPosition(
            this -> shape.getPosition().x + ( this -> shape.getGlobalBounds().width / 2.f ) - ( this -> text.getGlobalBounds().width / 2.f ),
            this -> shape.getPosition().y + ( this -> shape.getGlobalBounds().height / 2.f ) - ( this -> text.getGlobalBounds().height / 2.f ) - this -> text.getCharacterSize() / 4
        );
    }

    //====================================================
    //     setTextSize
    //====================================================
    /**
     * @brief Method used to set the text size.
     * 
     * @param size The new size to be set.
     */
    void Widget::setTextSize( int32_t size ){
        this -> text.setCharacterSize( size );
    }

    //====================================================
    //     setOutlineColor
    //====================================================
    /**
     * @brief Method used to set the outline color of the widget.
     * 
     * @param color The color to be set.
     */
    void Widget::setOutlineColor( const sf::Color& color ){
        this -> shape.setOutlineColor( color );
    }

    //====================================================
    //     setOutlineThickness
    //====================================================
    /**
     * @brief Method used to set the outline thickness of the widget.
     * 
     * @param thickness The outline thickness to be set.
     */
    void Widget::setOutlineThickness( float thickness ){
        this -> shape.setOutlineThickness( - thickness );
    }

    //====================================================
    //     setTextColor
    //====================================================
    /**
     * @brief Method used to set the color of the widget text.
     * 
     * @param color The new color to be set.
     */
    void Widget::setTextColor( const sf::Color& color ){
        this -> text.setFillColor( color );
    }
}
