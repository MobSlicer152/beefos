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

.PHONY: all clean help test beefiso usb
.SUFFIXES: .c .o .S

all: $(BUILD_DIR) $(BUILD_DIR)/beefkern $(BUILD_DIR)/klibc.a $(BUILD_DIR)/beefkern-arch.a iso

help:
	@echo "---<==[ BEEFOS KERNEL TARGETS ]==>---"
	@echo "all	- Build all targets"
	@echo "clean	- Delete build files"
	@echo "beefiso	- Build an ISO image"
	@echo "usb	- Puts the kernel and GRUB on a USB"
	@echo "test	- Run the ISO image in QEMU"
	@echo "help	- Display this help list"

beefiso: $(BUILD_DIR)/beefkern $(BUILD_DIR)
	mkdir -p $(BUILD_DIR)/isosrc/boot/grub
	cp src/grub.cfg $(BUILD_DIR)/isosrc/boot/grub
	cp $(BUILD_DIR)/beefkern $(BUILD_DIR)/isosrc/boot
	grub-mkrescue -o $(BUILD_DIR)/beefos.iso $(BUILD_DIR)/isosrc
	rm -rf $(BUILD_DIR)/isosrc

usb:
	@read -p "Enter device name: " USB_DEV; \
	echo "Using device '$$USB_DEV'"; \
	mkfs.fat $$USB_DEV; \
	mkdir -p $(ROOT)/usb/boot/grub; \
	mount $$USB_DEV $(ROOT)/usb; \
	cp $(ROOT)/src/grub.cfg $(ROOT)/usb/boot/grub
	cp $(BUILD_DIR)/beefkern $(ROOT)/usb/boot

.c.o:
	$(CC) -T$(ROOT)/src/link.ld $(CFLAGS) -o $@ -c $<

.S.o:
	$(CC) -T$(ROOT)/src/link.ld $(CFLAGS) -o $@ -c $<

clean:
	rm -rf $(BUILD_DIR)
	rm $(shell find src -type f | grep -i o$)

$(BUILD_DIR)/beefkern-arch.a: $(BUILD_DIR)
	$(MAKE) -C src/kern/arch/$(KERN_ARCH)

$(BUILD_DIR)/klibc.a: $(BUILD_DIR)/beefkern-arch.a $(BUILD_DIR)
	cp src/kern/arch/$(KERN_ARCH)/vga.h include/beefos
	$(MAKE) -C src/klibc

$(BUILD_DIR)/beefkern: $(BUILD_DIR)/klibc.a $(BUILD_DIR)/beefkern-arch.a $(BUILD_DIR)
	$(MAKE) -C src/kern

test: beefiso
	qemu-system-i386 -cdrom $(BUILD_DIR)/beefos.iso

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)
