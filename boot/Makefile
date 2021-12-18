include $(ROOT)/efi.mak

HERE = $(shell pwd)

EFI_CFLAGS += -I$(HERE)/include

BOOT_SRCS = $(addprefix $(HERE)/src/, main.c util.c)
BOOT_OBJS = $(BOOT_SRCS:%.c=%.o)

all: $(BOOT_OBJS) $(BIN_DIR)/boot.efi

$(BOOT_OBJS): $(BOOT_SRCS)
$(BIN_DIR)/boot.efi: $(BOOT_OBJS) $(GNUEFI_OBJS)
	$(LD) $(EFI_LDFLAGS) $^ -o $@

