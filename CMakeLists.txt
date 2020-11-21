cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_COMPILER "clang")
set(CMAKE_EXE_LINKER "ld.lld")
set(CMAKE_ASM_COMPILER "clang")

project(BeefOS VERSION 0.0.1 LANGUAGES C ASM)

set(CMAKE_C_FLAGS "-ffreestanding -nostdlib --target=$ENV{TARGET} -march=$ENV{BUILD_ARCH} -Wall -Wextra")
set(CMAKE_EXE_LINKER_FLAGS "-T${CMAKE_CURRENT_LIST_DIR}/src/link.ld --target=$ENV{TARGET} -march=$ENV{BUILD_ARCH}")
set(CMAKE_ASM_FLAGS "--target=$ENV{TARGET} -march=$ENV{BUILD_ARCH}")

include_directories(include src/kern)

add_subdirectory(src)
