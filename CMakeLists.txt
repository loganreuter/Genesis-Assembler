set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

cmake_minimum_required(VERSION 3.9.1)

project(
    Genesis 
    VERSION 0.2 
    LANGUAGES C
)

add_library(AssemblerLib asm/asm.c asm/lexer.c asm/regex.c)

add_executable(asm asm/assembler.c)

target_link_libraries(asm PUBLIC AssemblerLib)