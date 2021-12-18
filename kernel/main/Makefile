include $(KERNEL_ROOT)/kernel.mak

HERE = $(shell pwd)

KERNEL_CFLAGS += -I$(HERE)/include
KERNEL_LDFLAGS += -Wl,-subsystem:native \
		  -Wl,-entry:kernel_main \
		  -Wl,-base:0xC0000000

KERNEL_MAIN_SRCS = $(addprefix $(HERE)/src/, main.c)
KERNEL_MAIN_OBJS = $(KERNEL_MAIN_SRCS:%.c=%.o)

all: $(KERNEL_MAIN_OBJS) $(BIN_DIR)/kernel.sys

$(KERNEL_MAIN_OBJS): $(KERNEL_MAIN_SRCS)
$(BIN_DIR)/kernel.sys: $(KERNEL_MAIN_OBJS)
	$(LD) $(KERNEL_LDFLAGS) $^ -o $@
