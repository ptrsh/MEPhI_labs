cmake_minimum_required(VERSION 3.20)

project(lab5 VERSION 1.0.0 LANGUAGES C ASM_NASM)

set(EXECUTABLE lab.out)

option(ASSEMBLER "Use assembly implementation" ON)

file(COPY assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(${EXECUTABLE} main.c)

if (ASSEMBLER)
    message("Using ASM implementation")
else ()
    set(OPTIMIZATION "0" CACHE STRING "Optimization level")
    add_compile_options(-g0 -O${OPTIMIZATION})
    message("Using C implementation with optimization: ${OPTIMIZATION}")
endif ()

add_subdirectory(lib)

target_include_directories(${EXECUTABLE} PUBLIC lib)

target_link_libraries(${EXECUTABLE} lib)
