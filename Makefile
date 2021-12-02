export

ARCH := $(shell uname -m | sed s/i[3456789]86/ia32/)

EFI_CRT0 := /usr/lib/crt0-efi-$(ARCH).o
EFI_LDSCRIPT := /usr/lib/elf_$(ARCH)_efi.lds

CFLAGS := -fno-stack-protector -fPIC -fshort-wchar \
	  -mno-red-zone -Wall -Wextra
LDFLAGS := -nostdlib -znocombreloc -T $(EFI_LDSCRIPT) \
	   -shared -Bsymbolic $(EFI_CRT0)

.PHONY: help list targets

help:
	@printf  "<---[ BEEFOS MAKEFILE INFORMATION ]--->\n \
	\n \
	Targets:\n \
	\n \
	\tboot.efi\t- Build the bootloader\n \
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

