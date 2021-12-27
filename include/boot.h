#pragma once

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include <efi.h>

// Data given to the kernel when it's started
struct kernel_boot_data {
	EFI_RUNTIME_SERVICES *efi_rt; // EFI runtime services
	void *memory_map; // Memory map
	size_t memory_map_size; // Total size of the memory map
	size_t memory_map_ent_size; // Size of one memory map entry
	void *rsdp; // ACPI Root System Descriptor pointer
	uint32_t *framebuffer; // Framebuffer address
	size_t framebuffer_size; // Size of the framebuffer in memory
	size_t framebuffer_width; // Width in pixels of the framebuffer
	size_t framebuffer_height; // Height in pixels of the framebuffer
	size_t framebuffer_scanline_pixels; // Number of pixels per scanline for the framebuffer
	bool framebuffer_bgr; // Whether the framebuffer uses BGR instead of RGB
};

// Jumps to the kernel's entry point
extern void enter_kernel(void *entry, void *stack, size_t stack_size, struct kernel_boot_data *data);
