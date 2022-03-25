@echo off

if not "%BEEFOS_BUILDENV%" == "1" (
	call %~dp0buildenv.bat
)

echo Building BeefOS...
msbuild %* -M:%NPROC% %~dp0..\beefos.sln
if not "%ERRORLEVEL%" == "0" (
	goto err
)

echo Creating boot disk...
oscdimg
if not "%ERRORLEVEL%" == "0" (
	goto err
)

:success
echo.
echo BUILD SUCCEEDED
goto :eof

:err
echo.
echo BUILD FAILED
goto :eof

