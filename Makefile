export

ARCH := $(shell uname -m)

ROOT = $(shell pwd)
BIN_DIR = $(ROOT)/bin

CC := clang
LD := $(CC)

GLOBAL_INCLUDES := $(addprefix -I, $(ROOT)/include)

.PHONY: help list targets clean

all: $(BIN_DIR) $(BIN_DIR)/boot.efi $(BIN_DIR)/boot.img kernel

$(BIN_DIR)/boot.efi: $(BIN_DIR)
	$(MAKE) -C boot $(BIN_DIR)/boot.efi

kernel: $(BIN_DIR)
	$(MAKE) -C kernel all

$(BIN_DIR)/boot.img: $(BIN_DIR) $(BIN_DIR)/boot.efi kernel
	dd if=/dev/zero of=$@ bs=1M count=100
	mformat -F -i $@
	mmd -i $@ ::/EFI
	mmd -i $@ ::/EFI/boot
	mmd -i $@ ::/beefos
	mcopy -i $@ $(BIN_DIR)/boot.efi ::/EFI/boot/bootx64.efi
	mcopy -i $@ $(BIN_DIR)/kernel.sys ::/beefos/kernel.sys

$(BIN_DIR):
	mkdir -p $@

clean:
	rm -rf $(BIN_DIR)
	rm -f $(ROOT)/compile_commands.json
	rm -f $(shell find -type f -iregex '.*\.o')

help:
	@printf  "<---[ BEEFOS MAKEFILE INFORMATION ]--->\n \
	\n \
	Targets:\n \
	\n \
	    all\t\t\t\t- Build everything\n \
	    $(BIN_DIR)/boot.img\t\t- Create a bootable image (requires mtools)\n \
	    $(BIN_DIR)/boot.efi\t\t- Build the bootloader\n \
	    kernel\t\t\t\t- Build all the kernel targets\n \
	    clean\t\t\t\t- Clean built files\n \
	\n \
	Kernel targets:\n \
	\n \
	    $(BIN_DIR)/kernel.sys\t- Build the kernel binary\n"

list: help
targets: help

