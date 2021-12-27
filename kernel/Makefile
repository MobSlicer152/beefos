export

KERNEL_ROOT = $(ROOT)/kernel

include kernel.mak

all: $(BIN_DIR)/kernel_graphics.lib $(BIN_DIR)/kernel_util.lib $(BIN_DIR)/kernel.sys

$(BIN_DIR)/kernel_graphics.lib: $(BIN_DIR)
	$(MAKE) -C graphics all

$(BIN_DIR)/kernel_util.lib: $(BIN_DIR)
	$(MAKE) -C util all

$(BIN_DIR)/kernel.sys: $(BIN_DIR) $(BIN_DIR)/kernel_util.lib $(BIN_DIR)/kernel_graphics.lib
	$(MAKE) -C main all
