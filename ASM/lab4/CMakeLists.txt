cmake_minimum_required(VERSION 3.20)

project(lab4 VERSION 1.0.0 LANGUAGES ASM_NASM)

set(SOURCE lab.s)
set(OBJECTS lab.o)
set(EXECUTABLE lab.out)

set(LIBPATH /lib/gcc/x86_64-linux-gnu/9)
set(OBJPATH /usr/lib/x86_64-linux-gnu)
set(PREOBJ "${OBJPATH}/crt1.o ${OBJPATH}/crti.o")
set(POSTOBJ ${OBJPATH}/crtn.o)
set(LIBS "-lgcc -lgcc_eh -lc -lm")

SET(CMAKE_C_FLAGS_DEBUG "-D_DEBUG")
set(CMAKE_C_LINK_EXECUTABLE "ld -static -L ${LIBPATH} ${PREOBJ} ${OBJECTS} ${POSTOBJ} -\( ${LIBS} -\) -o ${EXECUTABLE}")
set(SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/${SOURCE})

set_source_files_properties(${SOURCE} PROPERTIES LANGUAGE ASM_NASM COMPILE_FLAGS "-g -F dwarf")

add_custom_command(
    OUTPUT ${OBJECTS}
    COMMAND nasm -f elf64 -g -F dwarf -o ${OBJECTS} ${SOURCE}
    DEPENDS ${SOURCE}
)

add_executable(${EXECUTABLE} ${SOURCE} ${OBJECTS})

set_target_properties(${EXECUTABLE} PROPERTIES LINKER_LANGUAGE C)

