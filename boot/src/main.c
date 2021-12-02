#include <efi.h>
#include <efilib.h>

EFI_STATUS EFIAPI efi_main(EFI_HANDLE image_handle, EFI_SYSTEM_TABLE *system_table)
{
	ST = system_table;

	uefi_call_wrapper(ST->ConOut->OutputString, 2, ST->ConOut, L"Hello, World!\n");

	return EFI_SUCCESS;
}

