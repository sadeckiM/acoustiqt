file(GLOB_RECURSE FIRMWARE_FILES
    "src/*.cpp" 
    "include/*.hh" 
    "platformio.ini"
    "../shared/*.hh"
)

add_custom_target(esp32_sources SOURCES ${FIRMWARE_FILES})
