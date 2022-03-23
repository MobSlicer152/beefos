#include <efi.h>
#include <efilib.h>

#include "executable.h"

void uefi_main(void)
{
	ST->ConOut->OutputString(ST->ConOut, L"Loading BeefOS...\n");
	while (1);
}
