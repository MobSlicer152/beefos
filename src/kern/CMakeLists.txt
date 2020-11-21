cmake_minimum_required(VERSION 3.10)

include_directories(${CMAKE_CURRENT_LIST_DIR} $ENV{GRUB_DIR} $ENV{GRUB_DIR}/include)

set(KERN_C_SRC
	init/main.c
)

set(KERN_X86_C_SRC
	arch/$ENV{KERN_ARCH}/tty.c
)

set(KERN_X86_ASM_SRC
	arch/$ENV{KERN_ARCH}/boot.S
	arch/$ENV{KERN_ARCH}/crti.S
	arch/$ENV{KERN_ARCH}/crtn.S
)

set(KERN_X86_SRC
	${KERN_X86_ASM_SRC}
	${KERN_X86_C_SRC}
)

add_executable(beefkern ${KERN_C_SRC} ${KERN_X86_SRC})
target_link_libraries(beefkern klibc)

add_custom_command(TARGET beefkern POST_BUILD COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:beefkern> ${CMAKE_BINARY_DIR}/beefkern)
