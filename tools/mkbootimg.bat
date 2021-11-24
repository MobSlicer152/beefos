@echo off

pushd %~dp0

pushd ..

set "log=%CD%\bin\bootimg.log"
set "img=%CD%\bin\boot.img"
set "grub_cfg=%CD%\grub.cfg"
set "bootsector=%CD%\bin\boot.bin"
set "vhd_letter=s"
set "vhd_mount=%vhd_letter%:"

:: Erase the log
if exist %log% del /f/q %log%

:: Make sure the output folder is there
if not exist %CD%\bin (
	echo The kernel hasn't been built yet
	goto :eof
)

goto success

:success
	popd
	echo Done
	goto :eof

:error
	popd
	del /f/q %script% %vhd%
	echo Error occurred, boot image may not have been created correctly. See %log% for more information
	goto :eof
