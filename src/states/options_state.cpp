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
        already_wrote_player( false ),
        already_wrote_speed( false ),
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
        sf::Sprite snake_branch_sprite( state_texture_1 );
        snake_branch_sprite.setPosition( 
           0, 
           ( this -> game_window_size_y - snake_branch_sprite.getGlobalBounds().height ) * 0.25f
        );

        // Settings logo
        sf::Sprite settings_logo( state_texture_3 );
        settings_logo.setPosition( 
           ( this -> game_window_size_x - settings_logo.getGlobalBounds().width ) * 0.5f,
           ( this -> game_window_size_y - settings_logo.getGlobalBounds().height ) * 0.3f
        );

        // Background
        sf::RectangleShape background( sf::Vector2f( this -> game_window_size_x, this -> game_window_size_y ) );
        background.setTexture( &state_texture_2, true );

        // Drawing the images
        this -> game_window -> draw( background );
        this -> game_window -> draw( snake_branch_sprite );
        this -> game_window -> draw( settings_logo );
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

        // Player option text
        this -> player_option.setFillColor( sf::Color::Black );
        this -> player_option.setPosition( x_pos * 0.7f, y_pos * 1.03f );
        this -> player_option.setCharacterSize( 30 );

        // Text has been saved text (player)
        this -> text_has_been_saved_player.setFillColor( sf::Color::Black );
        this -> text_has_been_saved_player.setPosition( 
            x_pos * 1.25f, 
            this -> player_option.getPosition().y
        );
        this -> text_has_been_saved_player.setCharacterSize( 30 );

        // Speed option text
        this -> speed_option.setFillColor( sf::Color::Black );
        this -> speed_option.setPosition( this -> player_option.getPosition().x, this -> player_option.getPosition().y * 1.2f );
        this -> speed_option.setCharacterSize( 30 );

        // Snake speed textbox
        this -> snake_speed_textbox = { 
            std::shared_ptr<widget::Textbox> ( new widget::Textbox( 
                x_pos, y_pos * 1.21f, width, height, font, "",
                idleColor, hoverColor, activeColor ) 
            )
        };
        this -> snake_speed_textbox -> setTextSize( text_size );
        this -> snake_speed_textbox -> setTextColor( textColor );

        // Text has been saved text (speed)
        this -> text_has_been_saved_speed.setFillColor( sf::Color::Black );
        this -> text_has_been_saved_speed.setPosition( 
            this -> text_has_been_saved_player.getPosition().x,
            this -> speed_option.getPosition().y
        );
        this -> text_has_been_saved_speed.setCharacterSize( 30 );
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
    void OptionsState::fileUpdate( std::string_view option, int16_t option_idx ) const {

        // Variables
        std::ifstream input_file( this -> options_file_path );
        std::vector<std::string> lines;
        std::string input;

        // Reading file lines
        while( std::getline( input_file, input ) ){
            lines.push_back( input );
        }
        
        // Modifying the interested line
        lines.at( option_idx ) = option;
        
        // Close the input stream
        input_file.close();

        // Write updates in the output file
        std::ofstream output_file( this -> options_file_path );
        for( const auto& line: lines ){
            output_file << line << "\n";
        }
        
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
        this -> speed_option.setString( "Change snake speed:" );

        // Text has been saved (speed)) settings
        this -> text_has_been_saved_speed.setFont( this -> font );
        this -> text_has_been_saved_speed.setString( "Saved!" );

        // Draw stuff
        this -> game_window -> draw( this -> back_to_menu );
        this -> game_window -> draw( this -> player_option );
        this -> game_window -> draw( this -> speed_option );
        this -> player_name_textbox -> pack( this -> game_window );
        this -> snake_speed_textbox -> pack( this -> game_window );

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
    }
}