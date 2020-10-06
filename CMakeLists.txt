cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_COMPILER "clang")
set(CMAKE_EXE_LINKER "ld.lld")
set(CMAKE_ASM_COMPILER "clang")

set(CMAKE_C_FLAGS "-ffreestanding -nostdlib --target=i686-elf -march=i686 -Wall -Wextra")
set(CMAKE_EXE_LINKER_FLAGS "-T${CMAKE_CURRENT_LIST_DIR}/src/link.ld --target=i686-elf -march=i686")
set(CMAKE_ASM_FLAGS "--target=i686-elf -march=i686")

project(BeefOS VERSION 0.0.1 LANGUAGES C ASM)

include_directories(include src/kern)

add_subdirectory(src)
