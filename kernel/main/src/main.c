#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "boot.h"

void kernel_main(struct kernel_boot_data *data)
{
	data->efi_rt->ResetSystem(EfiResetCold, EFI_SUCCESS, 0, NULL);
}
