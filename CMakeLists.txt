cmake_minimum_required(VERSION 3.11) # FetchContent is available in 3.11+
project(3draylib)

#add_link_options(-static -static-libgcc -static-libstdc++)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
set(RAYLIB_VERSION 5.5)
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
        game.cpp
        game.h
        player.cpp
        player.h
        camera3D.cpp
        camera3D.h
        map.cpp
        map.h
        mainmenu.cpp
        mainmenu.h
        button.cpp
        button.h
        settingsmenu.cpp
        settingsmenu.h)

target_link_libraries(${PROJECT_NAME} raylib)

add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/shaders
        $<TARGET_FILE_DIR:${PROJECT_NAME}>/shaders
)

#add_custom_command(
#        TARGET ${PROJECT_NAME} POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy_directory
#        ${CMAKE_CURRENT_SOURCE_DIR}/IronMan
#        $<TARGET_FILE_DIR:${PROJECT_NAME}>/IronMan
#)

# Set the build type to Debug by default
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif()

# Add a debug macro for debug builds
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(DEBUG_MODE)
endif()

# Apply static linking only for Windows
if(WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -static-libgcc -static-libstdc++")
else()
    # Use dynamic linking on Linux and ensure Wayland support
    set(CMAKE_EXE_LINKER_FLAGS "") # Remove static linking
    set(GLFW_USE_WAYLAND ON)
    set(GLFW_BUILD_X11 OFF) # Disable X11 support
endif()
