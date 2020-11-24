KLIBC_OBJS=kabrt/kabort.o     \
	   kitoa/kitoa.o      \
	   kprintf/kprintf.o  \
	   kstring/kmemcmp.o  \
	   kstring/kmemcpy.o  \
	   kstring/kmemmove.o \
	   kstring/kmemset.o  \
	   kstring/kstrlen.o  \
	   kstring/memcpy.o

DIR=$(CURDIR)

.SUFFIXES: .c .o

.c.o:
	$(CC) -T$(ROOT)/src/link.ld $(CFLAGS) -o $@ -c $<

$(BUILD_DIR)/klibc.a: $(KLIBC_OBJS) $(BUILD_DIR)/beefkern-arch.a
	mkdir -p $(BUILD_DIR)/tmp
	cd $(BUILD_DIR)/tmp
	$(AR) x $(BUILD_DIR)/beefkern-arch.a
	cd $(DIR)
	cp $(KLIBC_OBJS) $(BUILD_DIR)/tmp
	$(AR) crs $@ $(BUILD_DIR)/tmp/*.o
	rm -rf $(BUILD_DIR)/tmp
