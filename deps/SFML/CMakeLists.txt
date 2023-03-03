# Finding the package
find_package( SFML 2.5.1 COMPONENTS system window graphics audio )

# Fetching the package if not found
if( NOT SFML_FOUND )

    # Fetching the package
    include( FetchContent )

    FetchContent_Declare(
      SFML
      GIT_REPOSITORY "https://github.com/SFML/SFML"
      GIT_TAG 2.5.1
    )

    # No need to build audio and network modules
    set( SFML_BUILD_NETWORK FALSE )

    # Make it available
    message( STATUS "Fetching SFML..." )
    FetchContent_MakeAvailable( SFML )
endif()