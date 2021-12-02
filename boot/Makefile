include $(ROOT)/efi.mak

BOOT_SRCS = $(addprefix src/, main.c)
BOOT_OBJS = $(BOOT_SRCS:%.c=%.o)

all: $(BOOT_OBJS) $(BIN_DIR)/boot.efi

$(BOOT_OBJS): $(BOOT_SRCS)
$(BIN_DIR)/boot.efi: $(BOOT_OBJS) $(GNUEFI_OBJS)
	$(LD) $(EFI_LDFLAGS) $^ -o $@

