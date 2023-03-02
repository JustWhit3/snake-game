//====================================================
//     File data
//====================================================
/**
 * @file game_window.cpp
 * @author Gianluca Bianco (biancogianluca9@gmail.com)
 * @date 2022-12-19
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
#include <windows/pause_window.hpp>

// States
#include <states/menu_state.hpp>
#include <states/state.hpp>

// Utility
#include <utility/gui.hpp>

// SFML
#include <SFML/Graphics/Image.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>

// Debug
#ifdef DEBUG_SNAKE_GAME
    #include <ptc/print.hpp>
#endif

// STD
#include <memory>
#include <unordered_map>
#include <string>
#include <string_view> 
#include <utility>
#include <filesystem>
#include <fstream>

namespace snake::window{

    //====================================================
    //     GameWindow
    //====================================================
    /**
     * @brief Default constructor of the class. It creates the game window.
     * 
     */
    GameWindow::GameWindow(){
    
        // Initialize window parameters
        this -> create( utility::getDesktopMode(), "Snake Game" );

        // Setting the icon
        auto icon = sf::Image{};
        icon.loadFromFile( "img/images/logo_icon.png" );
        this -> setIcon( icon.getSize().x, icon.getSize().y, icon.getPixelsPtr() );
    
        // Other settings
        this -> setPosition( sf::Vector2i( 
                this -> desktop.width * 0.5 - this -> getSize().x * 0.5, 
                this -> desktop.height * 0.5 - this -> getSize().y * 0.5 
            ) 
        );

        // Create game files
        this -> createGameFiles();

        // Push the Menu state
        this -> game_window_states.insert( { "Menu", std::make_shared<state::MenuState>( state::MenuState( this ) ) } );

        // Init variables
        this -> scores_container = this -> getScoresContainer();

        // Display the window
        while( this -> isOpen() ){

            // Run the window event
            runWindow();

            // Draw the first element of the states map
            this -> game_window_states.begin() -> second -> drawState();
        }
    }

    //====================================================
    //     runWindow
    //====================================================
    /**
     * @brief Method used to run the main window.
     * 
     */
    void GameWindow::runWindow(){
        
        // Check events of the main window
        while( this -> pollEvent( game_event ) ){
        
            // Handling different events
            switch( game_event.type ){
            
                // Window closing
                case sf::Event::Closed:
                    eventClosed();
                    break;
                        
                // Key pressed in window
                case sf::Event::KeyPressed:
                    eventKeyPressed( game_event );
                    break;
    
                // Default cases
                default:
                    break;
            }
        }
    }

    //====================================================
    //     eventClosed
    //====================================================
    /**
     * @brief Method used to deal with the the event closed case.
     * 
     */
    void GameWindow::eventClosed(){

        // Menu  / Options / Scores state
        if( game_window_states.begin() -> first == "Menu" || game_window_states.begin() -> first == "Options" || game_window_states.begin() -> first == "Scores" ){
            this -> close();
        }

        // Game state
        else if( game_window_states.begin() -> first == "Game" ){
            auto pause_window{ PauseWindow( "Pause" ) };
        }
    }

    //====================================================
    //     eventKeyPressed
    //====================================================
    /**
     * @brief Method used to deal with the the event key pressed case.
     * 
     */
    void GameWindow::eventKeyPressed( const sf::Event& event ){

        // Menu  / Options / Scores state
        if( game_window_states.begin() -> first == "Menu" ){
            switch( event.key.code ){
                case sf::Keyboard::Escape:{ // ESC
                    this -> close();
                    break;
                }
                default:
                    break;
            }
        }

        // Game state
        else if( game_window_states.begin() -> first == "Game" ){
            switch( event.key.code ){
                case sf::Keyboard::Escape:{ // Esc
                    auto pause_window{ PauseWindow( "Pause" ) };
                    if( pause_window.back_to_menu == true ) {
                        this -> game_window_states.erase( "Game" );
                    }
                    break;
                }
                default:
                    break;
            }
        }

        // Options state
        else if( game_window_states.begin() -> first == "Options" ){
            switch( event.key.code ){
                case sf::Keyboard::Escape:{ // ESC
                    this -> close();
                    break;
                }
                case sf::Keyboard::Tab:{ // Tab
                    this -> close();
                    auto game_window{ GameWindow() };
                    break;
                }
                default:
                    break;
            }
        }

        // Scores state
        else if( game_window_states.begin() -> first == "Scores" ){
            switch( event.key.code ){
                case sf::Keyboard::Escape:{ // ESC
                    this -> close();
                    break;
                }
                case sf::Keyboard::Tab:{ // Tab
                    this -> close();
                    auto game_window{ GameWindow() };
                    break;
                }
                default:
                    break;
            }
        }
    }

    //====================================================
    //     getScoresContainer
    //====================================================
    /**
     * @brief Method used to get scores container.
     * 
     */
    std::vector<uint64_t> GameWindow::getScoresContainer() const {

        // Read scores from file
        std::ifstream score_file( this -> score_file_path );
        if( ! score_file ){
            std::ofstream default_settings( this -> score_file_path );
            default_settings.close();
        }
        std::string score_line;
        std::vector<std::string> lines;
        while( std::getline( score_file, score_line ) ){
            lines.push_back( score_line );
        }

        // Compute best score
        std::vector <uint64_t> scores_container;
        std::string player_name;
        uint64_t player_score;
        for( const auto& line: lines ){
            std::stringstream words( line );
            words >> player_score >> player_name;
            scores_container.push_back( static_cast<uint64_t>( player_score ) );
        }

        // Close stream
        score_file.close();

        return scores_container;
    }

    //====================================================
    //     createGameFiles
    //====================================================
    /**
     * @brief Method used to create game directories and files.
     * 
     */
    void GameWindow::createGameFiles(){

        // Create the game directory name
        #ifdef _WIN32
            this -> game_directory_oss << "C:\\Users\\" << this -> username << "\\snake-game_files";
            this -> options_file_oss << "C:\\Users\\" << this -> username << "\\snake-game_files\\snake-game_options.txt";
            this -> score_file_oss << "C:\\Users\\" << this -> username << "\\snake-game_files\\snake-game_score.txt";
        #else
            this -> game_directory_oss << "/home/" << this -> username << "/snake-game_files";
            this -> options_file_oss << "/home/" << this -> username << "/snake-game_files/snake-game_options.txt";
            this -> score_file_oss << "/home/" << this -> username << "/snake-game_files/snake-game_score.txt";
        #endif
        
        // Create dirs
        std::filesystem::create_directory( game_directory_oss.str() );

        // Create file names
        this -> options_file_path = options_file_oss.str();
        this -> score_file_path = score_file_oss.str();

        // Fill options file with default values
        if( ! std::ifstream( options_file_path ) ){
            std::ofstream default_settings( options_file_path );
            default_settings << "Player: Unknown\n"
                             << "SpeedPlus: 25\n"
                             << "Background: default\n";
            default_settings.close();
        }
    }    
}