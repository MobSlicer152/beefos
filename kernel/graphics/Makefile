include $(KERNEL_ROOT)/kernel.mak

HERE = $(shell pwd)

KERNEL_CFLAGS += $(addprefix -I, $(HERE)/include $(HERE)/../util/include)

KERNEL_GRAPHICS_SRCS = $(addprefix $(HERE)/src/, pixel.c rect.c screen.c)
KERNEL_GRAPHICS_OBJS = $(KERNEL_GRAPHICS_SRCS:%.c=%.o)

all: $(KERNEL_GRAPHICS_OBJS) $(BIN_DIR)/kernel_graphics.lib

$(KERNEL_GRAPHICS_OBJS): $(KERNEL_GRAPHICS_SRCS)
$(BIN_DIR)/kernel_graphics.lib: $(KERNEL_GRAPHICS_OBJS)
	$(AR) $(KERNEL_ARFLAGS) $^ -out:$@
