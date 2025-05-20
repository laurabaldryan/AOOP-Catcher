cmake_minimum_required(VERSION 3.16)
project(OOCatcher)

set(CMAKE_CXX_STANDARD 17)

# Set the path to Raylib
set(RAYLIB_DIR "C:/Libraries/raylib")  # <-- Adjust if needed

# Include Raylib headers
include_directories(${RAYLIB_DIR}/include)
link_directories(${RAYLIB_DIR}/lib)

# Add your source files
add_executable(OOCatcher
        main.cpp
        point.cpp
        base_line.cpp
        line1.cpp
        line2.cpp
        limb.cpp
        body.cpp
        config.h
)

# Link Raylib and system dependencies
target_link_libraries(OOCatcher
        raylib
        opengl32
        gdi32
        winmm
        kernel32  # for threads
        user32    # optional, for input events
)
