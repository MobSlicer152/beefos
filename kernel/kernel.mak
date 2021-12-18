KERNEL_INCLUDES = $(GLOBAL_INCLUDES) $(addprefix -I, $(ROOT)/deps/stb $(KERNEL_ROOT)/include)
KERNEL_CFLAGS = -target $(ARCH)-unknown-windows -ffreestanding \
		-fshort-wchar -mno-red-zone -Wall -Wextra \
	        -Wno-unknown-pragmas -Wno-unused-parameter \
	        -Wno-incompatible-pointer-types $(KERNEL_INCLUDES)
KERNEL_LDFLAGS = -target $(ARCH)-unknown-windows -nostdlib \
		 -fuse-ld=lld-link

%.o: %.c
	$(CC) $(KERNEL_CFLAGS) -c -o $@ $<
