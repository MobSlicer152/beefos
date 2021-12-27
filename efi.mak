EFI_ARCH := $(shell uname -m | sed s/i[3456789]86/ia32/)

EFI_INCLUDES = $(GLOBAL_INCLUDES) $(addprefix -I, /usr/include/efi)
EFI_CFLAGS = -target $(ARCH)-unknown-windows -g -ffreestanding \
	      -fshort-wchar -mno-red-zone -Wall -Wextra \
	      -Wno-unknown-pragmas -Wno-unused-parameter \
	      -Wno-incompatible-pointer-types $(EFI_INCLUDES)
EFI_ASFLAGS = -fwin64 $(EFI_INCLUDES)
EFI_LDFLAGS = -fuse-ld=lld-link -target $(ARCH)-unknown-windows \
	       -nostdlib -Wl,-entry:efi_main -Wl,-subsystem:efi_application \
	       -Wl,-debug

GNUEFI_SRCS = $(addprefix $(ROOT)/deps/gnuefi/, cmdline.c console.c data.c debug.c \
		dpath.c error.c event.c guid.c misc.c print.c str.c stubs.c \
		runtime/efirtlib.c runtime/rtdata.c runtime/rtlock.c runtime/rtstr.c \
		runtime/vm.c $(ARCH)/math.c)
GNUEFI_OBJS = $(GNUEFI_SRCS:%.c=%.o)

$(GNUEFI_OBJS): $(GNUEFI_SRCS)

%.o: %.c
	$(CC) $(EFI_CFLAGS) -c -o $@ $<

%.o: %.asm
	$(AS) $(EFI_ASFLAGS) -o $@ $<

