#include <efi.h>
#include <efilib.h>

EFI_STATUS EFIAPI efi_main(EFI_HANDLE image_handle,
			   EFI_SYSTEM_TABLE *system_table)
{
	ST = system_table;
	BS = ST->BootServices;

	Print(L"System information:\nFirmware vendor: %ls\nFirmware revision: %d\n",
	      ST->FirmwareVendor, ST->FirmwareRevision);

	return EFI_SUCCESS;
}
