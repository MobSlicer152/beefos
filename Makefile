export

AR=$(TARGET)-ar
AS=$(TARGET)-as
CC=$(TARGET)-gcc
LD=$(TARGET)-ld
MAKE=make

ROOT=$(shell pwd)
BUILD_DIR=$(ROOT)/$(BUILDDIR)

CFLAGS=-g -O2 -ffreestanding -Wall -Wextra -I$(ROOT)/include -I$(ROOT)/$(GRUB_DIR) -I$(ROOT)/$(GRUB_DIR)/include
LDFLAGS=-nostdlib
LIBS=-lgcc

.PHONY: all clean help test beefiso
.SUFFIXES: .c .o .S

all: $(BUILD_DIR)/beefkern $(BUILD_DIR)/klibc.a $(BUILD_DIR)/beefkern-arch.a iso

help:
	@echo "---<==[ BEEFOS KERNEL TARGETS ]==>---"
	@echo "all   - Build all targets"
	@echo "clean - Delete build files"
	@echo "iso   - Build an ISO image"
	@echo "test  - Run the ISO image in QEMU"
	@echo "help  - Display this help list"

iso: $(BUILD_DIR)/beefkern
	mkdir -p $(BUILD_DIR)/isosrc/boot/grub
	cp src/grub.cfg $(BUILD_DIR)/isosrc/boot/grub
	cp $(BUILD_DIR)/beefkern $(BUILD_DIR)/isosrc/boot
	grub-mkrescue -o $(BUILD_DIR)/beefos.iso $(BUILD_DIR)/isosrc
	rm -rf $(BUILD_DIR)/isosrc

.c.o:
	$(CC) -T$(ROOT)/src/link.ld $(CFLAGS) -o $@ -c $<

.S.o:
	$(CC) -T$(ROOT)/src/link.ld $(CFLAGS) -o $@ -c $<

clean:
	rm -rf $(BUILD_DIR)
	rm $(shell find src -type f | grep -i o$)

$(BUILD_DIR)/beefkern-arch.a:
	$(MAKE) -C src/kern/arch/$(KERN_ARCH)

$(BUILD_DIR)/klibc.a: $(BUILD_DIR)/beefkern-arch.a
	cp src/kern/arch/$(KERN_ARCH)/vga.h include/beefos
	$(MAKE) -C src/klibc

$(BUILD_DIR)/beefkern: $(BUILD_DIR)/klibc.a $(BUILD_DIR)/beefkern-arch.a
	$(MAKE) -C src/kern

test:
	qemu-system-i386 -cdrom $(BUILD_DIR)/beefos.iso
