KERN_OBJS=init/main.o

.SUFFIXES: .c .o

.c.o:
	$(CC) -T$(ROOT)/src/link.ld $(CFLAGS) -o $@ -c $<

$(BUILD_DIR)/beefkern: $(KERN_OBJS) $(BUILD_DIR)/klibc.a $(BUILD_DIR)/beefkern-arch.a
	$(CC) -T$(ROOT)/src/link.ld $(CFLAGS) $(LDFLAGS) -o $@ $^
