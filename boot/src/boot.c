#include <efi.h>
#include <efilib.h>

#include "executable.h"

EFI_STATUS uefi_main(EFI_HANDLE image_handle, EFI_SYSTEM_TABLE *system_table)
{
	ST = system_table;
	BS = ST->BootServices;
	RT = ST->RuntimeServices;

	while (1)
		ST->ConOut->OutputString(ST->ConOut, L"Loading BeefOS...\n");
}
