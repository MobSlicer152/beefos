export

AR=$(TARGET)-ar
AS=$(TARGET)-as
CC=$(TARGET)-gcc
LD=$(TARGET)-ld
MAKE=make

ROOT=$(shell pwd)
BUILD_DIR=$(ROOT)/$(BUILDDIR)
GRUB_DIR=$(ROOT)/$(GRUBDIR)

CFLAGS=-g -O2 -ffreestanding -Wall -Wextra -I$(ROOT)/include -I$(GRUB_DIR) -I$(GRUB_DIR)/include
LDFLAGS=-nostdlib
LIBS=-lgcc

.PHONY: all clean help test beefiso usb grub chk-kern-mboot
.SUFFIXES: .c .o .S

all: $(BUILD_DIR) grub $(BUILD_DIR)/beefkern $(BUILD_DIR)/klibc.a $(BUILD_DIR)/beefkern-arch.a beefiso

help:
	@echo "---<==[ BEEFOS KERNEL TARGETS ]==>---"
	@echo "all		- Build all targets"
	@echo "clean		- Delete build files"
	@echo "beefiso		- Build an ISO image"
	@echo "usb		- Puts the kernel and GRUB on a USB"
	@echo "grub		- Fetches and configures the GRUB sources"
	@echo "chk-kern-mboot	- Checks whether the kernel is recognized as Multiboot by GRUB"
	@echo "test		- Run the ISO image in QEMU"
	@echo "help		- Display this help list"

beefiso: $(BUILD_DIR)/beefkern $(BUILD_DIR)
	mkdir -p $(BUILD_DIR)/isosrc/boot/grub
	cp src/grub.cfg $(BUILD_DIR)/isosrc/boot/grub
	cp $(BUILD_DIR)/beefkern $(BUILD_DIR)/isosrc/boot
	grub-mkrescue -o $(BUILD_DIR)/beefos.iso $(BUILD_DIR)/isosrc
	rm -rf $(BUILD_DIR)/isosrc

usb: $(BUILD_DIR)/beefkern $(BUILD_DIR)
	@read -p "Enter USB device name: " USB_DEV; \
	echo "Using device '$$USB_DEV'"; \
	parted -a optimal $$USB_DEV mklabel msdos; \
	parted -a optimal $$USB_DEV mkpart primary fat32 0% 100%; \
	mkfs.fat -F 32 -n "BEEFOS" "$$USB_DEV"1; \
	mkdir -p $(ROOT)/usb; \
	mount "$$USB_DEV"1 $(ROOT)/usb; \
	mkdir -p $(ROOT)/usb/boot/grub; \
	cp $(ROOT)/src/grub.cfg $(ROOT)/usb/boot/grub; \
	cp $(BUILD_DIR)/beefkern $(ROOT)/usb/boot; \
	grub-install --root-directory=$(ROOT)/usb $$USB_DEV --target=$(GRUB_TGT)
	umount $(ROOT)/usb
	rm -r $(ROOT)/usb

$(ROOT)/grub.tar.xz $(GRUB_DIR):
	@echo "Finding latest GRUB source tarball..."
	@GRUB_FTP_PATH=`curl -fsSL https://ftp.gnu.org/find.txt.gz | gzip -d | grep '^\./gnu/grub' | grep '\.tar\.xz$$' | sed 's/^\.\///' | sort -V | tail -n1`; \
		GRUB_TARBALL=`echo $$GRUB_FTP_PATH | sed 's/^gnu\/grub\///'`; \
		echo "Downloading $$GRUB_TARBALL..."; \
		curl -fGL https://ftp.gnu.org/$$GRUB_FTP_PATH -o grub.tar.xz; \
		rm -rf $(GRUB_DIR); \
		mkdir -p $(GRUB_DIR); \
		tar -C $(GRUB_DIR) --strip-components=1 -xf $(ROOT)/grub.tar.xz; \
		cd $(GRUB_DIR); \
		AR=x86_64-linux-gnu-ar AS=x86_64-linux-gnu-as CC=x86_64-linux-gnu-gcc LD=x86_64-linux-gnu-ld $(GRUB_DIR)/configure --host=x86_64-linux-gnu --target=x86_64-linux-gnu; \
		cd $(ROOT)

grub: $(ROOT)/grub.tar.xz $(GRUB_DIR)

update-grub:
	rm -rf $(ROOT)/grub.tar.xz $(GRUB_DIR)
	$(MAKE) grub

chk-kern-mboot:
	grub-file --is-x86-multiboot $(BUILD_DIR)/beefkern

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

$(BUILD_DIR)/beefkern: $(BUILD_DIR)/klibc.a $(BUILD_DIR)/beefkern-arch.a $(BUILD_DIR) grub
	$(MAKE) -C src/kern

test: beefiso
	qemu-system-i386 -cdrom $(BUILD_DIR)/beefos.iso

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)
