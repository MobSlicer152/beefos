cmake_minimum_required(VERSION 3.10)

set(KLIBC_C_SRC
	kabrt/kabort.c
	kitoa/kitoa.c
	kprintf/kprintf.c
	kstring/kmemcmp.c
	kstring/kmemcpy.c
	kstring/kmemmove.c
	kstring/kmemset.c
	kstring/kstrlen.c
	kstring/memcpy.c
)

add_library(klibc ${KLIBC_C_SRC})
target_link_libraries(klibc gcc)

add_custom_command(TARGET klibc POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:klibc> ${CMAKE_BINARY_DIR}/klibc.a)
