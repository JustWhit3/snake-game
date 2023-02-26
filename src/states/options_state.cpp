//====================================================
//     File data
//====================================================
/**
 * @file options_state.cpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2022-12-24
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

// States
#include <states/state.hpp>
#include <states/options_state.hpp>
#include <states/menu_state.hpp>
#include <states/game_state.hpp>

// STD
#include <utility>

namespace snake::state{

    //====================================================
    //     OptionsState (constructor)
    //====================================================
    /**
     * @brief Constructor of the OptionsState class.
     * 
     * @param game_window The window to which the state stuff is constructed.
     */
    OptionsState::OptionsState( window::GameWindow* game_window ): 
        game_window( game_window ){

        // Draw widgets
        this -> drawWidgets();
    }

    //====================================================
    //     drawState
    //====================================================
    /**
     * @brief Method used to draw the current state.
     * 
     */
    void OptionsState::drawState() {

        // Clear the window
        this -> game_window -> clear( this -> background_color );

        // Update player entry
        this -> updateEnteredText();

        // Drawing images
        this -> drawImg();

        // Drawing widgets
        this -> setWidgetsKeys();
        this -> packWidgets();

        // Display the state
        this -> game_window -> display();
    }

    //====================================================
    //     drawImg
    //====================================================
    /**
     * @brief Method used to draw the images.
     * 
     */
    void OptionsState::drawImg() const {

        // Loading files from textures
        if( ! state_texture_1.loadFromFile( "img/snake_branch.png" ) ){
            this -> game_window -> close();
        }
        if( ! state_texture_2.loadFromFile( "img/menu_background.jpg" ) ){
            this -> game_window -> close();
        }

        // Snake on the branch
        sf::Sprite snake_branch_sprite( state_texture_1 );
        snake_branch_sprite.setPosition( 
           0, 
           ( this -> game_window_size_y - snake_branch_sprite.getGlobalBounds().height ) * 0.25f
        );

        // Background
        sf::RectangleShape background( sf::Vector2f( this -> game_window_size_x, this -> game_window_size_y ) );
        background.setTexture( &state_texture_2, true );

        // Drawing the images
        this -> game_window -> draw( background );
        this -> game_window -> draw( snake_branch_sprite );
    }

    //====================================================
    //     drawWidgets
    //====================================================
    /**
     * @brief Method used to draw widgets in the current state.
     * 
     */
    void OptionsState::drawWidgets() {

        // Back-to-menu text
        this -> back_to_menu.setFillColor( sf::Color::Black );
        this -> back_to_menu.setPosition( 
            this -> game_window -> getSize().x * 0.03f, 
            this -> game_window -> getSize().y * 0.91f 
        );
        this -> back_to_menu.setCharacterSize( 30 );

        // Textbox constants
        const float width{ this -> game_window_size_y * 0.2f };
        const float height{ width * 0.35f };
        const float x_pos = ( this -> game_window_size_x * 0.5f - width * 0.5f );
        constexpr int32_t text_size{ 24 };
        const sf::Font font{ this -> font };
        const sf::Color idleColor{ sf::Color( 102, 204, 0 ) };
        const sf::Color hoverColor{ sf::Color( 255, 102, 102 ) };
        const sf::Color textColor{ sf::Color::Black };

        // Player name textbox
        this -> player_name_textbox = { 
            std::shared_ptr<widget::Textbox> ( new widget::Textbox( 
                x_pos, this -> game_window_size_y * 0.5f - height * 0.5f + 80.f, width, height, font, "",
                idleColor, hoverColor ) 
            )
        };
        this -> player_name_textbox -> setTextSize( text_size );
        this -> player_name_textbox -> setTextColor( textColor );
    }

    //====================================================
    //     setWidgetsKeys
    //====================================================
    /**
     * @brief Method used to set widgets in the current state.
     * 
     */
    void OptionsState::setWidgetsKeys() const {

    }

    //====================================================
    //     updatePlayerEntry
    //====================================================
    /**
     * @brief Method used to update the entered text.
     * 
     */
    void OptionsState::updateEnteredText() {
        if( this -> game_window -> game_event.type == sf::Event::TextEntered ){
            switch( this -> game_window -> game_event.text.unicode ){

                // Delete case
                case '\b':{ 
                    this -> player_name_current = this -> player_name_textbox -> text.getString();
                    if( this -> player_name_current.size() > 0 ){
                        this -> player_name_textbox -> text.setString( 
                            player_name_current.erase( player_name_current.size() - 1, 1 ) 
                        );
                    }
                    break;
                }

                // Other cases
                default:{
                    this -> player_name_input += this -> game_window -> game_event.text.unicode;
                    this -> player_name_text.setString( this -> player_name_input );
                    this -> player_name_textbox -> text.setString( this -> player_name_text.getString() );
                    break;
                }
            }
        }
    }

    //====================================================
    //     packWidgets
    //====================================================
    /**
     * @brief Method used to pack widgets in the current state.
     * 
     */
    void OptionsState::packWidgets(){

        // Back-to-menu text settings
        this -> back_to_menu.setFont( this -> font );
        this -> back_to_menu.setString( "Press <Tab> to back to menu" );

        // Draw stuff
        this -> game_window -> draw( this -> back_to_menu );
        this -> player_name_textbox -> pack( this -> game_window );
    }
}