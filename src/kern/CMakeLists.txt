cmake_minimum_required(VERSION 3.10)

include_directories(include ${CMAKE_CURRENT_LIST_DIR})

set(KERN_C_SRC
	kern/main.c
)

set(KERN_I386_C_SRC
	arch/i386/tty.c
)

set(KERN_I386_ASM_SRC
	arch/i386/boot.S 
	arch/i386/crti.S
	arch/i386/crtn.S
)

set(KERN_I386_SRC
	${KERN_I386_ASM_SRC}
	${KERN_I386_C_SRC}
)

add_subdirectory(klibc)

add_executable(beefkern ${KERN_C_SRC} ${KERN_I386_SRC})
target_link_libraries(beefkern klibc gcc)

add_custom_command(TARGET beefkern POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:beefkern> ${CMAKE_BINARY_DIR}/beefkern)
