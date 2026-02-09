cmake_minimum_required(VERSION 3.16)
project(ITCrowdDVDGame LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find SFML
find_package(SFML 3 COMPONENTS system window graphics audio REQUIRED)

# Create executable
add_executable(game Main.cpp)

# Link SFML libraries
target_link_libraries(game PRIVATE 
    sfml-system
    sfml-window
    sfml-graphics
    sfml-audio
)

# Copy assets folder to build directory
add_custom_command(TARGET game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets
        $<TARGET_FILE_DIR:game>/assets
)

# Set working directory for Visual Studio
set_property(TARGET game PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")

# Windows-specific settings
if(WIN32)
    # Copy SFML DLLs to build directory on Windows
    if(BUILD_SHARED_LIBS)
        add_custom_command(TARGET game POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
                $<TARGET_FILE:sfml-system>
                $<TARGET_FILE:sfml-window>
                $<TARGET_FILE:sfml-graphics>
                $<TARGET_FILE:sfml-audio>
                $<TARGET_FILE_DIR:game>
        )
    endif()
endif()
