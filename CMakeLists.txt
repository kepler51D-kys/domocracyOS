cmake_minimum_required(VERSION 3.12)
project(DomocracyOS VERSION 1.0 LANGUAGES C)

enable_language(ASM_NASM)

find_program(GRUB_MKRESCUE grub-mkrescue REQUIRED)
find_program(MKDIR mkdir REQUIRED)
find_program(CP cp REQUIRED)

set(C_FLAGS
    -m32
    -ffreestanding
    -fno-stack-protector
    -fno-pic
    -mno-red-zone
    -march=i686
    -O2
    -Wall
    -Wextra
    -std=gnu99
)

# set(LINKER_FLAGS
#     -m elf_i386
#     -nostdlib
#     -T ${CMAKE_SOURCE_DIR}/linker.ld
#     -n
# )

set(ASM_NASM_FLAGS
    -f elf32
)

set(SOURCES
    src/kernel.asm  
    src/kernel.c
    libs/segTable.c
)

add_executable(kernel ${SOURCES})

target_include_directories(kernel PRIVATE include)

target_compile_options(kernel PRIVATE $<$<COMPILE_LANGUAGE:C>:${C_FLAGS}>)
target_compile_options(kernel PRIVATE $<$<COMPILE_LANGUAGE:ASM_NASM>:${ASM_NASM_FLAGS}>)
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
    COMMAND ${GRUB_MKRESCUE} -o domocracyos.iso iso
    COMMENT "Building ISO"
)

add_custom_target(domocracyos.iso DEPENDS iso)

add_custom_target(DomocracyOS DEPENDS domocracyos.iso)

add_custom_target(clean-all
    COMMAND rm -rf iso domocracyos.iso iso-stamp
    COMMAND make clean
    COMMENT "Cleaning"
)