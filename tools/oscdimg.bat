@echo off

if not "%BEEFOS_BUILDENV%" == "1" (
	%~dp0buildenv
)

:: Get the absolute path to the root directory so the virtual disk driver doesn't freak out
for /f "usebackq tokens=3" %%i in (`cmd /c dir %~dp0.. ^| findstr "Directory of"`) do (
	set "root=%%i"
)

set "tools=%root%\tools"
set "bin_dir=%root%\bin"
set "diskpart_script=%bin_dir%\diskpart.txt"
set "fattools=%root%\deps\fattools"
set "boot_img=%bin_dir%\boot.vhdx"
set "boot_letter=z"
set "boot_src=%boot_letter%:\"

if not exist %bin_dir% mkdir %bin_dir%

:: Make absolutely sure the boot image doesn't conflict
call :unmount
del /s/q/f %boot_img%

echo Creating boot image...
echo create vdisk file="%boot_img%" maximum=200 type=expandable> %diskpart_script%
echo attach vdisk>> %diskpart_script%
echo convert gpt>> %diskpart_script%
echo create part primary>> %diskpart_script%
echo format fs=fat32 label=BEEFOS quick>> %diskpart_script%
echo assign letter="%boot_letter%">> %diskpart_script%

diskpart /S %diskpart_script%

echo Copying files...
mkdir %boot_src%\EFI\boot
copy %bin_dir%\boot.efi %boot_src%\EFI\boot\bootx64.efi
copy %tools%\OpenShell.efi %boot_src%\shellx64.efi

call :unmount

echo Done. If no errors occured you should have %boot_img%.
goto :eof

:unmount
echo Unmounting...
echo sel vdisk file="%boot_img%"> %diskpart_script%
echo sel part 2 >> %diskpart_script%
echo remove letter="%boot_letter%">> %diskpart_script%
echo detach vdisk noerr>> %diskpart_script%

diskpart /S %diskpart_script%

rmdir /s/q %boot_src%

