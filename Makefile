export

ARCH := $(shell uname -m | sed s/i[3456789]86/ia32/)

ROOT = $(shell pwd)
BIN_DIR = $(ROOT)/bin

CC := clang
LD := $(CC)

.PHONY: help list targets clean

all: $(BIN_DIR) $(BIN_DIR)/boot.efi

$(BIN_DIR)/boot.efi: $(BIN_DIR) $(OBJ_DIR)
	$(MAKE) -C boot all

$(BIN_DIR):
	mkdir -p $@

clean:
	rm -rf $(BIN_DIR)
	rm -f $(shell find -type f -iregex '.*\.o')

help:
	@printf  "<---[ BEEFOS MAKEFILE INFORMATION ]--->\n \
	\n \
	Targets:\n \
	\n \
	\tall\t\t- Build everything\n \
	\t$(BIN_DIR)/boot.efi\t- Build the bootloader\n \
	\tclean\t\t- Clean built files\n \
	\n \
	Flags:\n \
	\n \
	\tARCH\t\t= $(ARCH)\n \
	\tEFI_CRT0\t= $(EFI_CRT0)\n \
	\tEFI_LDSCRIPT\t= $(EFI_LDSCRIPT)\n \
	\tCFLAGS\t\t= $(CFLAGS)\n \
	\tLDFLAGS\t\t= $(LDFLAGS)\n"

list: help
targets: help

