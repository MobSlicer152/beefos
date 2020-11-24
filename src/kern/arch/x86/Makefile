ARCH_OBJS=boot.S.o \
	  crti.S.o \
	  crtn.S.o \
	  tty.c.o

.SUFFIXES: .c .o .S

.S.o:
	$(CC) -T$(ROOT)/src/link.ld $(CFLAGS) -o $@ -c $<

.c.o:
	$(CC) -T$(ROOT)/src/link.ld $(CFLAGS) -o $@ -c $<

$(BUILD_DIR)/beefkern-arch.a: $(ARCH_OBJS)
	$(AR) crs $(BUILD_DIR)/beefkern-arch.a $(ARCH_OBJS)
