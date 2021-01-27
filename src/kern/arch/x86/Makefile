ARCH_OBJS=crti.o \
	  crtn.o \
	  tty.o

.SUFFIXES: .c .o .S

.S.o:
	$(CC) -T$(ROOT)/src/link.ld $(CFLAGS) -o $@ -c $<

.c.o:
	$(CC) -T$(ROOT)/src/link.ld $(CFLAGS) -o $@ -c $<

$(BUILD_DIR)/beefkern-arch.a: $(ARCH_OBJS)
	$(AR) crs $@ $^
