KERN_OBJS=arch/$(KERN_ARCH)/boot.o \
	  init/main.o

.SUFFIXES: .c .o

.c.o:
	$(CC) -T$(ROOT)/src/link.ld $(CFLAGS) -o $@ -c $<

$(BUILD_DIR)/beefkern: $(KERN_OBJS) $(BUILD_DIR)/beefkern-arch.a $(BUILD_DIR)/klibc.a
	$(CC) -T$(ROOT)/src/link.ld $(CFLAGS) $(LDFLAGS) -o $@ $^
