cmake_minimum_required(VERSION 3.11) # FetchContent is available in 3.11+
project(3draylib)

#add_link_options(-static -static-libgcc -static-libstdc++)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
set(RAYLIB_VERSION 5.0)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
    include(FetchContent)
    FetchContent_Declare(
            raylib
            DOWNLOAD_EXTRACT_TIMESTAMP OFF
            URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    )
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
        set(FETCHCONTENT_QUIET NO)
        FetchContent_MakeAvailable(raylib)
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
    endif()
endif()

add_executable(${PROJECT_NAME} main.cpp
        game.h
        game.cpp
        game.h
        player.cpp
        player.h
        camera3D.cpp
        camera3D.h
        map.cpp
        map.h
        mainmenu.cpp
        mainmenu.h)
target_link_libraries(${PROJECT_NAME} raylib)

# Set the build type to Debug by default
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Add a debug macro for debug builds
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(DEBUG_MODE)
endif()