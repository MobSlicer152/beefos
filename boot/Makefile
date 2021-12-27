include $(ROOT)/efi.mak

HERE = $(shell pwd)

EFI_CFLAGS += -I$(HERE)/include
EFI_LDFLAGS += -Wl,-pdb:$(BIN_DIR)/boot.pdb

BOOT_SRCS = $(addprefix $(HERE)/src/, main.c util.c)
BOOT_ASM_SRCS = $(addprefix $(HERE)/src/$(ARCH)/, enter_kernel.asm)
BOOT_OBJS = $(BOOT_SRCS:%.c=%.o) $(BOOT_ASM_SRCS:%.asm=%.o)

all: $(BOOT_OBJS) $(BIN_DIR)/boot.efi

$(BOOT_OBJS): $(BOOT_SRCS)
$(BIN_DIR)/boot.efi: $(BOOT_OBJS) $(GNUEFI_OBJS)
	$(LD) $(EFI_LDFLAGS) $^ -o $@

