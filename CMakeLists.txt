cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_COMPILER "$ENV{TARGET}-gcc")
set(CMAKE_EXE_LINKER "$ENV{TARGET}-ld")
set(CMAKE_ASM_COMPILER "$ENV{TARGET}-as")

set(CMAKE_C_FLAGS "-ffreestanding -nostdlib -Wall -Wextra")
set(CMAKE_EXE_LINKER_FLAGS "-T${CMAKE_CURRENT_LIST_DIR}/src/link.ld")

set(CMAKE_C_COMPILER_WORKS 1)
set(CMAKE_EXE_LINKER_WORKS 1)
set(CMAKE_ASM_COMPILER_WORKS 1)

project(BeefOS VERSION 0.0.1 LANGUAGES C ASM)

add_subdirectory(src/)
