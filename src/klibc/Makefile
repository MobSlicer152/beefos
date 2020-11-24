KLIBC_OBJS=kabrt/kabort.c.o     \
	   kitoa/kitoa.c.o      \
	   kprintf/kprintf.c.o  \
	   kstring/kmemcmp.c.o  \
	   kstring/kmemcpy.c.o  \
	   kstring/kmemmove.c.o \
	   kstring/kmemset.c.o  \
	   kstring/kstrlen.c.o  \
	   kstring/memset.c.o

.c.o:
	$(CC) -T$(ROOT)/src/link.ld $(CFLAGS) -o $@ -c $<

$(BUILD_DIR)/klibc.a: $(KLIBC_OBJS)
	$(AR) rcT $(BUILD_DIR)/klibc.a src/kern/arch/$(KERN_ARCH)/*.o $(BUILD_DIR)/beefkern-arch.a
