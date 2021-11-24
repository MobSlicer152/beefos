; Bootsector

; Set up the data segment and jump to the entry point
mov ax, 0x07c0
mov ds, ax
jmp main

; Include functions
%include "x86/print.inc"

; Entry point
main:
	; Print a startup message
	mov si, startup_msg
	call bios_print

	; Hang after the code finishes
	jmp hang

startup_msg: db "Loading BeefOS...", 0x0D, 0x0A, 0x00

; Hang indefinitely
hang:
	jmp SHORT hang

times 440 - ($ - $$) db 0

; Disk signature
dd 0x69696969
dw 0x0000

; Partition table

; Partition table entry structure
STRUC mbr_partition
	.bootable: resb 1
	.start_head: resb 1
	.start_sector_cylinder: resw 1
	.system_id: resb 1
	.end_head: resb 1
	.end_sector_cylinder: resw 1
	.relative_sector: resb 4 ; The MBR isn't aligned for these to be read into registers
	.total_sectors: resb 4
ENDSTRUC

; Partitions
%define MAX_PARTITIONS 4
%define PARTITION_COUNT 1

; FAT32
partition_1:
	db 0x80 ; Bootable
	db 0x00 ; Unused
	dw 0x0000 ; Unused
	db 0x0b ; Type (FAT32)
	dw 0x0000 ; Unused
	dd 0x00000001 ; Start sector
	dd 0x03200000 ; Number of sectors (100M)

times (MAX_PARTITIONS - PARTITION_COUNT) * mbr_partition_size + 1 db 0

db 0x55
db 0xAA
