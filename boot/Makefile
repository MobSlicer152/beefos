include $(ROOT)/efi.mak

EFI_CFLAGS += -I$(shell pwd)/include

BOOT_SRCS = $(addprefix src/, main.c)
BOOT_OBJS = $(BOOT_SRCS:%.c=%.o)

all: $(BOOT_OBJS) $(BIN_DIR)/boot.efi

$(BOOT_OBJS): $(BOOT_SRCS)
$(BIN_DIR)/boot.efi: $(BOOT_OBJS) $(GNUEFI_OBJS)
	$(LD) $(EFI_LDFLAGS) $^ -o $@

