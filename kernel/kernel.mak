KERNEL_INCLUDES = $(GLOBAL_INCLUDES) $(addprefix -I, /usr/include/efi \
		  $(ROOT)/deps/stb $(KERNEL_ROOT)/include)
KERNEL_CFLAGS = -target $(ARCH)-unknown-windows -g -ffreestanding \
		-fshort-wchar -mno-red-zone -Wall -Wextra \
	        -Wno-unknown-pragmas -Wno-unused-parameter \
	        -Wno-incompatible-pointer-types $(KERNEL_INCLUDES)
KERNEL_LDFLAGS = -fuse-ld=lld-link -target $(ARCH)-unknown-windows \
		 -nostdlib -Wl,-debug

%.o: %.c
	$(CC) $(KERNEL_CFLAGS) -c -o $@ $<
