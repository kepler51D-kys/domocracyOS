cmake_minimum_required(VERSION 3.12)

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
set(CMAKE_C_COMPILER /home/pilkey/opt/cross/bin/i686-elf-gcc)

project(DomocracyOS VERSION 1.0 LANGUAGES C ASM_NASM)

find_program(NASM_EXECUTABLE nasm REQUIRED)
find_program(GRUB_MKRESCUE grub-mkrescue REQUIRED)
find_program(MKDIR mkdir REQUIRED)
find_program(CP cp REQUIRED)

set(C_FLAGS
    -m32
    -ffreestanding
    -fno-stack-protector
    -fno-pic
    -mno-red-zone
    -O2
    -Wall
    -Wextra
)

set(LINKER_FLAGS
    -nostdlib
    -static
#    -lgcc
    -T ${CMAKE_SOURCE_DIR}/linker.ld
)

set(C_SOURCES
    src/kernel.c
    libs/segTable.c
)

set(NASM_SOURCES
    src/boot.asm
)

set(NASM_OBJECTS)

# Loop through NASM sources and create custom commands for each
foreach(ASM_FILE IN LISTS NASM_SOURCES)
    get_filename_component(ASM_NAME ${ASM_FILE} NAME_WE)
    set(ASM_OBJ ${CMAKE_BINARY_DIR}/${ASM_NAME}.o)
    list(APPEND NASM_OBJECTS ${ASM_OBJ})

    add_custom_command(
        OUTPUT ${ASM_OBJ}
        COMMAND ${NASM_EXECUTABLE} -f elf32 -o ${ASM_OBJ} ${CMAKE_SOURCE_DIR}/${ASM_FILE}
        DEPENDS ${CMAKE_SOURCE_DIR}/${ASM_FILE}
        COMMENT "Assembling ${ASM_FILE}"
    )
endforeach()

add_custom_target(asm_objects ALL DEPENDS ${NASM_OBJECTS})

add_executable(kernel ${C_SOURCES} ${NASM_OBJECTS})
add_dependencies(kernel asm_objects)


target_include_directories(kernel PRIVATE include)
target_compile_options(kernel PRIVATE $<$<COMPILE_LANGUAGE:C>:${C_FLAGS}>)
target_link_options(kernel PRIVATE ${LINKER_FLAGS})

add_custom_command(
    OUTPUT ${CMAKE_BINARY_DIR}/iso-stamp
    COMMAND ${MKDIR} -p iso/boot/grub
    COMMAND ${CP} ${CMAKE_BINARY_DIR}/kernel iso/boot/kernel.bin
    COMMAND ${CP} ${CMAKE_SOURCE_DIR}/grub.cfg iso/boot/grub/
    COMMAND ${CMAKE_COMMAND} -E touch ${CMAKE_BINARY_DIR}/iso-stamp
    DEPENDS kernel
    COMMENT "Preparing ISO"
)

add_custom_target(iso
    DEPENDS ${CMAKE_BINARY_DIR}/iso-stamp
    COMMAND ${GRUB_MKRESCUE} -o ../domocracyos.iso iso
    COMMENT "Building ISO"
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
)

add_custom_target(domocracyos.iso
    DEPENDS iso
)

add_custom_target(DomocracyOS DEPENDS domocracyos.iso)

add_custom_target(clean-all
    COMMAND rm -rf iso domocracyos.iso iso-stamp
    COMMAND make clean
    COMMENT "Cleaning"
)