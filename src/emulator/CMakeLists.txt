cmake_minimum_required(VERSION 3.24)
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED True)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(chip8 
    main.c
    system.c
    cpu.c
    mem.c
    timer.c
    display.c
    keypad.c
    instructions/memory.c
    instructions/condition.c
    instructions/flow.c
    instructions/display.c
    instructions/math.c
    instructions/io.c
    instructions/timer.c
    instructions/keys.c
)

target_link_libraries(chip8 logger)
target_link_libraries(chip8 -lmingw32 ${SDL2_LIBRARIES})
