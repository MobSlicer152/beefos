EFI_INCLUDES := $(addprefix -I, /usr/include/efi)
EFI_CFLAGS := -target x86_64-unknown-windows -ffreestanding \
	      -fshort-wchar -mno-red-zone -Wall -Wextra \
	      $(EFI_INCLUDES)
EFI_LDFLAGS := -target x86_64-unknown-windows -nostdlib \
	       -Wl,-entry:efi_main -Wl,-subsystem:efi_application \
	       -fuse-ld=lld-link

GNUEFI_SRCS = $(ROOT)/deps/gnuefi/data.c
GNUEFI_OBJS = $(GNUEFI_SRCS:%.c=%.o)

$(GNUEFI_OBJS): $(GNUEFI_SRCS)

%.o: %.c
	$(CC) $(EFI_CFLAGS) -c -o $@ $<

