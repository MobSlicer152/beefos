export

KERNEL_ROOT = $(ROOT)/kernel

include kernel.mak

all: $(BIN_DIR)/kernel.sys

$(BIN_DIR)/kernel.sys: $(BIN_DIR)
	$(MAKE) -C main all
