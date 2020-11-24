export

AR=ar
AS=$(TARGET)-as
CC=$(TARGET)-gcc
LD=$(TARGET)-ld
MAKE=make

ROOT=$(shell pwd)
BUILD_DIR=$(ROOT)/$(BUILDDIR)

CFLAGS=-g -O2 -ffreestanding -Wall -Wextra -I$(ROOT)/include
LDFLAGS=-nostdlib
LIBS=-lgcc

.PHONY: all clean help test
.SUFFIXES: .c .o .S

all: $(BUILD_DIR)/beefkern $(BUILD_DIR)/klibc.a $(BUILD_DIR)/beefkern-arch.a $(BUILD_DIR)/beefos.iso

help:
	echo "---<=:[ BEEFOS KERNEL TARGETS ]:=>---"

.c.o:
	$(CC) -T$(ROOT)/src/link.ld $(CFLAGS) -o $@ -c $<

.S.o:
	$(CC) -T$(ROOT)/src/link.ld $(CFLAGS) -o $@ -c $<

clean:
	rm -rf $(BUILD_DIR)
	rm **/*.o

$(BUILD_DIR)/beefkern:
	$(MAKE) -C src/kern

$(BUILD_DIR)/beefkern-arch.a:
	$(MAKE) -C src/kern/arch/$(KERN_ARCH)

$(BUILD_DIR)/klibc.a:
	$(MAKE) -C src/klibc
