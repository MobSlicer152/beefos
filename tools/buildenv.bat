@echo off

:: Try to set up a Visual C++ environment (copied from a script on my development drive)
for /F "tokens=* USEBACKQ" %%F in (`"%PROGRAMFILES(X86)%\Microsoft Visual Studio\Installer\vswhere.exe" -all -prerelease -latest -products * -property installationPath`) do (
	set vs2019_install=%%F
)

for /F "tokens=* USEBACKQ" %%F in (`type "%vs2019_install%\VC\Auxiliary\Build\Microsoft.VCToolsVersion.default.txt"`) do (
    set msvc_defaultver=%%F
)
echo Default MSVC version is %msvc_defaultver%
set msvc_path=%vs2019_install%\VC\Tools\MSVC\%msvc_defaultver%
c:
pushd "%vs2019_install%\VC\Auxiliary\Build"
call vcvarsall.bat x64
popd
%~d0

set PATH=%~dp0;%PATH%

set /a NPROC=%NUMBER_OF_PROCESSORS% + 2
set BEEFOS_BUILDENV=1
