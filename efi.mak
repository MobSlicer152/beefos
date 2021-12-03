EFI_INCLUDES += $(addprefix -I, /usr/include/efi $(ROOT)/deps/stb)
EFI_CFLAGS += -target x86_64-unknown-windows -ffreestanding \
	      -fshort-wchar -mno-red-zone -Wall -Wextra \
	      $(EFI_INCLUDES)
EFI_LDFLAGS += -target x86_64-unknown-windows -nostdlib \
	       -Wl,-entry:efi_main -Wl,-subsystem:efi_application \
	       -fuse-ld=lld-link

GNUEFI_SRCS = $(addprefix $(ROOT)/deps/gnuefi/, cmdline.c console.c data.c debug.c \
		dpath.c error.c event.c guid.c misc.c print.c str.c stubs.c \
		runtime/efirtlib.c runtime/rtdata.c runtime/rtlock.c runtime/rtstr.c \
		runtime/vm.c $(ARCH)/math.c)
GNUEFI_OBJS = $(GNUEFI_SRCS:%.c=%.o)

$(GNUEFI_OBJS): $(GNUEFI_SRCS)

%.o: %.c
	$(CC) $(EFI_CFLAGS) -c -o $@ $<

