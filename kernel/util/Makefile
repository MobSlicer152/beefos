include $(KERNEL_ROOT)/kernel.mak

HERE = $(shell pwd)

KERNEL_CFLAGS += $(addprefix -I, $(HERE)/include)

KERNEL_UTIL_ASM_SRCS = $(addprefix $(HERE)/src/, $(ARCH)/reverse.asm)
KERNEL_UTIL_OBJS = $(KERNEL_UTIL_SRCS:%.c=%.o) $(KERNEL_UTIL_ASM_SRCS:%.asm=%.o)

all: $(KERNEL_UTIL_OBJS) $(BIN_DIR)/kernel_util.lib

$(KERNEL_UTIL_OBJS): $(KERNEL_UTIL_SRCS)
$(BIN_DIR)/kernel_util.lib: $(KERNEL_UTIL_OBJS)
	$(AR) $(KERNEL_ARFLAGS) $^ -out:$@
