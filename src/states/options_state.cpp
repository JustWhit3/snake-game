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
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/System/Vector2.hpp>

// STD
#include <fstream>
#include <cstdint>
#include <algorithm>
#include <filesystem>
#include <memory>
#include <string>
#include <string_view>
#include <vector>

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
        already_wrote_player( false ),
        already_wrote_speed( false ),
        already_wrote_background( false ),
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
        this -> snake_speed_textbox -> updateText( this -> game_window -> game_event );
        this -> background_textbox -> updateText( this -> game_window -> game_event );

        // Drawing images
        this -> drawImg();

        // Drawing widgets
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
    void OptionsState::drawImg() {

        // Loading files from textures
        if( ! state_texture_1.loadFromFile( "img/images/snake_branch.png" ) ){
            this -> game_window -> close();
        }
        if( ! state_texture_2.loadFromFile( "img/images/menu_background.jpg" ) ){
            this -> game_window -> close();
        }
        if( ! state_texture_3.loadFromFile( "img/images/settings_logo.png" ) ){
            this -> game_window -> close();
        }

        // Snake on the branch
        this -> snake_branch_sprite.setTexture( this -> state_texture_1 );
        this -> snake_branch_sprite.setPosition( 
           0, 
           ( this -> game_window_size_y - this -> snake_branch_sprite.getGlobalBounds().height ) * 0.25f
        );

        // Settings logo
        this -> settings_logo.setTexture( state_texture_3 );
        this -> settings_logo.setPosition( 
           ( this -> game_window_size_x - this -> settings_logo.getGlobalBounds().width ) * 0.5f,
           ( this -> game_window_size_y - this -> settings_logo.getGlobalBounds().height ) * 0.2f
        );

        // Background
        this -> background.setSize( sf::Vector2f( this -> game_window_size_x, this -> game_window_size_y ) );
        this -> background.setTexture( &state_texture_2, true );

        // Drawing the images
        this -> game_window -> draw( this -> background );
        this -> game_window -> draw( this -> snake_branch_sprite );
        this -> game_window -> draw( this -> settings_logo );
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
        this -> back_to_menu.setFillColor( this -> textColor );
        this -> back_to_menu.setPosition( 
            game_window_size_x * 0.03f, 
            game_window_size_y * 0.91f 
        );
        this -> back_to_menu.setCharacterSize( this -> text_size + 6 );

        // Textbox constants
        this -> width = this -> game_window_size_y * 0.2f;
        this -> height = width * 0.35f;
        this -> x_pos = ( this -> game_window_size_x * 0.5f - this -> width * 0.5f ) * 1.2f;
        this -> y_pos = ( this -> game_window_size_y * 0.5f - this -> height * 0.5f + 80.f ) * 0.8f;
        this -> idleColor = sf::Color::White;
        this -> hoverColor = sf::Color( 224, 224, 224 );
        this -> activeColor = sf::Color( 192, 192, 192 );

        // Player name textbox
        this -> player_name_textbox = { 
            std::shared_ptr<widget::Textbox> ( new widget::Textbox( 
                    this -> x_pos, 
                    this -> y_pos, 
                    this -> width, 
                    this -> height, 
                    this -> font, 
                    "",
                    this -> idleColor, 
                    this -> hoverColor, 
                    this -> activeColor
                ) 
            )
        };
        this -> player_name_textbox -> setTextSize( this -> text_size );
        this -> player_name_textbox -> setTextColor( this -> textColor );

        // Player option text
        this -> player_option.setFillColor( this -> textColor );
        this -> player_option.setPosition( this -> x_pos * 0.7f, this -> y_pos * 1.03f );
        this -> player_option.setCharacterSize( this -> text_size + 6 );

        // Text has been saved text (player)
        this -> text_has_been_saved_player.setFillColor( this -> textColor );
        this -> text_has_been_saved_player.setPosition( 
            this -> x_pos * 1.25f, 
            this -> player_option.getPosition().y
        );
        this -> text_has_been_saved_player.setCharacterSize( this -> text_size + 6 );

        // Speed option text
        this -> speed_option.setFillColor( sf::Color::Black );
        this -> speed_option.setPosition( this -> player_option.getPosition().x * 0.78, this -> player_option.getPosition().y * 1.2f );
        this -> speed_option.setCharacterSize( this -> text_size + 6 );

        // Snake speed textbox
        this -> snake_speed_textbox = { 
            std::shared_ptr<widget::Textbox> ( new widget::Textbox( 
                    this -> x_pos, 
                    this -> y_pos * 1.21f, 
                    this -> width, 
                    this -> height, 
                    this -> font, 
                    "",
                    this -> idleColor, 
                    this -> hoverColor, 
                    this -> activeColor 
                ) 
            )
        };
        this -> snake_speed_textbox -> setTextSize( this -> text_size );
        this -> snake_speed_textbox -> setTextColor( this -> textColor );

        // Text has been saved text (speed)
        this -> text_has_been_saved_speed.setFillColor( this -> textColor );
        this -> text_has_been_saved_speed.setPosition( 
            this -> text_has_been_saved_player.getPosition().x,
            this -> speed_option.getPosition().y
        );
        this -> text_has_been_saved_speed.setCharacterSize( this -> text_size + 6 );

        // Background option text
        this -> background_option.setFillColor( this -> textColor );
        this -> background_option.setPosition( 
            this -> speed_option.getPosition().x * 0.76, 
            this -> speed_option.getPosition().y * 1.18f 
        );
        this -> background_option.setCharacterSize( this -> text_size + 6 );

        // Background option textbox
        this -> background_textbox = { 
            std::shared_ptr<widget::Textbox> ( new widget::Textbox( 
                    this -> x_pos, 
                    this -> y_pos * 1.43f, 
                    this -> width, 
                    this -> height, 
                    this -> font, 
                    "",
                    this -> idleColor, 
                    this -> hoverColor, 
                    this -> activeColor 
                ) 
            )
        };
        this -> background_textbox -> setTextSize( this -> text_size );
        this -> background_textbox -> setTextColor( this -> textColor );

        // Text has been saved text (background)
        this -> text_has_been_saved_background.setFillColor( this -> textColor );
        this -> text_has_been_saved_background.setPosition( 
            this -> text_has_been_saved_speed.getPosition().x,
            this -> background_option.getPosition().y
        );
        this -> text_has_been_saved_background.setCharacterSize( this -> text_size + 6 );
    }

    //====================================================
    //     fileUpdate
    //====================================================
    /**
     * @brief Method used to update the options file.
     * 
     * @param option The option to be modified.
     * @param option_idx File index of the option to be modified.
     */
    void OptionsState::fileUpdate( std::string_view option, uint16_t option_idx ){

        // Clear stuff from previous iterations
        this -> lines.clear();

        // Variables
        std::ifstream input_file( this -> options_file_path );

        // Reading file lines
        while( std::getline( input_file, this -> input ) ){
            lines.push_back( this -> input );
        }
        
        // Modifying the interested line
        this -> lines.at( option_idx ) = option;
        
        // Close the input stream
        input_file.close();

        // Write updates in the output file
        std::ofstream output_file( this -> options_file_path );
        std::for_each(
            this -> lines.begin(), 
            this -> lines.end(), 
            [ &output_file ]( auto& line ){ output_file << line << "\n"; } 
        );
        
        // Close the output file
        output_file.close();
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

        // Text has been saved (player) settings
        this -> text_has_been_saved_player.setFont( this -> font );
        this -> text_has_been_saved_player.setString( "Saved!" );

        // Player option text settings
        this -> player_option.setFont( this -> font );
        this -> player_option.setString( "Change player name:" );

        // Speed option text settings
        this -> speed_option.setFont( this -> font );
        this -> speed_option.setString( "Change snake speed (default 25):" );

        // Text has been saved (speed) settings
        this -> text_has_been_saved_speed.setFont( this -> font );
        this -> text_has_been_saved_speed.setString( "Saved!" );

        // Background option text settings
        this -> background_option.setFont( this -> font );
        this -> background_option.setString( "Change game background (insert file path):" );

        // Text has been saved (background) settings
        this -> text_has_been_saved_background.setFont( this -> font );
        this -> text_has_been_saved_background.setString( "Saved!" );

        // Draw stuff
        this -> game_window -> draw( this -> back_to_menu );
        this -> game_window -> draw( this -> player_option );
        this -> game_window -> draw( this -> speed_option );
        this -> game_window -> draw( this -> background_option );
        this -> player_name_textbox -> pack( this -> game_window );
        this -> snake_speed_textbox -> pack( this -> game_window );
        this -> background_textbox -> pack( this -> game_window );

        // Player option
        if( this -> player_name_textbox -> saved_text != "" ){

            // Write new options in file
            this -> game_window -> player_option = this -> player_name_textbox -> saved_text;
            if( this -> already_wrote_player == false ){
                this -> fileUpdate( "Player: " + this -> player_name_textbox -> saved_text.substr( 0, this -> player_name_textbox -> saved_text.size() - 1 ), 0 );
            }
            this -> already_wrote_player = true;
    
            // Draw temporary stuff
            if( this -> player_name_textbox -> deltaClock.getElapsedTime() < delta_time ){
                this -> game_window -> draw( this -> text_has_been_saved_player );
            }
        }

        // Speed option
        if( this -> snake_speed_textbox -> saved_text != "" ){

            // Write new options in file
            this -> game_window -> speed_option = this -> snake_speed_textbox -> saved_text;
            if( this -> already_wrote_speed == false ){
                this -> fileUpdate( "SpeedPlus: " + this -> snake_speed_textbox -> saved_text.substr( 0, this -> snake_speed_textbox -> saved_text.size() - 1 ), 1 );
            }
            this -> already_wrote_speed = true;
    
            // Draw temporary stuff
            if( this -> snake_speed_textbox -> deltaClock.getElapsedTime() < delta_time ){
                this -> game_window -> draw( this -> text_has_been_saved_speed );
            }
        }

        // Background option
        if( this -> background_textbox -> saved_text != "" ){

            // Write new options in file
            this -> game_window -> background_option = this -> background_textbox -> saved_text;
            if( this -> already_wrote_background == false ){
                this -> fileUpdate( "Background: " + this -> background_textbox -> saved_text.substr( 0, this -> background_textbox -> saved_text.size() - 1 ), 2 );
            }
            this -> already_wrote_background = true;
    
            // Draw temporary stuff
            if( this -> background_textbox -> deltaClock.getElapsedTime() < delta_time ){
                this -> game_window -> draw( this -> text_has_been_saved_background );
            }
        }
    }
}