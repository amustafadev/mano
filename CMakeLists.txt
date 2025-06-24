# CMake Version
cmake_minimum_required(VERSION 3.25)

# Set Project
project(mano)

# Use C++23
set(CMAKE_CXX_STANDARD 23)

# Define your executable
add_executable(mano main.cpp
        src/GapBuffer.cpp
        src/GapBuffer.h
        src/Console.cpp
        src/Console.h
        src/Editor.h
        src/Memory.h
        src/LineArray.cpp
        src/LineArray.h
        src/Application.cpp
        src/Application.h)

# Add Curses
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
target_link_libraries(mano ${CURSES_LIBRARIES})
