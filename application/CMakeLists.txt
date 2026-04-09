qt_add_executable(application
    WIN32 MACOSX_BUNDLE
    src/main.cpp
    src/mainwindow.cpp
    inc/mainwindow.hh
    src/mainwindow.ui
)

target_include_directories(application PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/inc")

target_link_libraries(application
    PRIVATE
        Qt6::Core
        Qt6::Widgets
)

target_compile_options(application PRIVATE
    -Wall
    -Wextra
    -pedantic
    -Werror=return-type
    -Werror=parentheses
    -Werror=vla
    -Werror=array-bounds
    -Wcast-qual
)

install(TARGETS application
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET application
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})

