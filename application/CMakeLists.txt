set(CMAKE_AUTOMOC ON) 
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(SOURCES
    src/main.cpp
    # src/microphone.cpp
    src/mainwindow.cpp
    inc/mainwindow.hh
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
