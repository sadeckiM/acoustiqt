cmake_minimum_required(VERSION 3.30)

project(AcoustiQt VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Multimedia)

add_subdirectory(firmware)
add_subdirectory(application)

