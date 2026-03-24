cmake_minimum_required(VERSION 3.20)
project(ACOUSTIQT VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_AUTOMOC ON) 
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets Multimedia)

set(SOURCES
    src/main.cpp
)

set(EXEC main)

add_executable(${EXEC} ${SOURCES})

target_include_directories(${EXEC} PRIVATE inc)

target_link_libraries(${EXEC} PRIVATE 
    Qt6::Widgets 
    Qt6::Multimedia
)

target_compile_options( ${EXEC} PRIVATE
    -Wall
    -Wextra
    -pedantic
    -Werror=return-type
    -Werror=parentheses
    -Werror=vla
    -Werror=array-bounds
    -Wcast-qual
    -Wmaybe-uninitialized
)
