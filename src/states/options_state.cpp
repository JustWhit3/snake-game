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

// Debug
#ifdef DEBUG_SNAKE_GAME
    #include <ptc/print.hpp>
#endif

// STD
#include <utility>
#include <fstream>

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
        game_window( game_window ), 
        already_wrote( false ),
        options_file_path( this -> game_window -> options_file_path ){

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
        this -> player_name_textbox -> updateText( this -> game_window -> game_event );

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
        const float x_pos = ( this -> game_window_size_x * 0.5f - width * 0.5f ) * 1.2f;
        const float y_pos = ( this -> game_window_size_y * 0.5f - height * 0.5f + 80.f );
        constexpr int32_t text_size{ 30 };
        const sf::Font font{ this -> font };
        const sf::Color idleColor{ sf::Color::White };
        const sf::Color hoverColor{ sf::Color( 224, 224, 224 ) };
        const sf::Color activeColor{ sf::Color( 192, 192, 192 ) };
        const sf::Color textColor{ sf::Color::Black };

        // Player name textbox
        this -> player_name_textbox = { 
            std::shared_ptr<widget::Textbox> ( new widget::Textbox( 
                x_pos, y_pos, width, height, font, "",
                idleColor, hoverColor, activeColor ) 
            )
        };
        this -> player_name_textbox -> setTextSize( text_size );
        this -> player_name_textbox -> setTextColor( textColor );

        // Text has been saved text
        this -> text_has_been_saved.setFillColor( sf::Color::Black );
        this -> text_has_been_saved.setPosition( x_pos * 1.25f, y_pos * 1.03f );
        this -> back_to_menu.setCharacterSize( 30 );

        // Player option text
        this -> player_option.setFillColor( sf::Color::Black );
        this -> player_option.setPosition( x_pos * 0.7f, y_pos * 1.03f );
        this -> player_option.setCharacterSize( 30 );
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

        // Text has been saved text settings
        this -> text_has_been_saved.setFont( this -> font );
        this -> text_has_been_saved.setString( "Saved!" );

        // Player option text settings
        this -> player_option.setFont( this -> font );
        this -> player_option.setString( "Change player name:" );

        // Draw stuff
        this -> game_window -> draw( this -> back_to_menu );
        this -> player_name_textbox -> pack( this -> game_window );
        this -> game_window -> draw( this -> player_option );

        // Draw temporary stuff
        if( this -> player_name_textbox -> saved_text != "" ){

            // Write new options in file
            this -> game_window -> player_option = this -> player_name_textbox -> saved_text;
            if( this -> already_wrote == false ){
                std::ofstream options_file( this -> options_file_path );
                
                options_file << "Player: " << this -> player_name_textbox -> saved_text.substr( 0, this -> player_name_textbox -> saved_text.size()-1) << "\n";
                options_file.close();
            }
            this -> already_wrote = true;
    
            // Draw temporary stuff
            if( this -> player_name_textbox -> deltaClock.getElapsedTime() < delta_time ){
                this -> game_window -> draw( this -> text_has_been_saved );
            }
        }
    }
}