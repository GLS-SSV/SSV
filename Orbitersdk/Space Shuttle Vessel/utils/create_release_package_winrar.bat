@echo off

set WINRAR_DIR="C:\Program Files\WinRAR\WinRAR.exe"

echo input major version number:
set /P "MAJOR_VERSION="

echo input minor version number:
set /P "MINOR_VERSION="

cls

set OUTPUT_NAME="SpaceShuttleVessel_v%MAJOR_VERSION%.%MINOR_VERSION%.zip"

echo creating %OUTPUT_NAME% in orbiter base directory...

cd ..\..\..

call %WINRAR_DIR% a -afzip -m5 %OUTPUT_NAME% "@Orbitersdk\Space Shuttle Vessel\utils\releasefilelist.txt"

@echo on

pause
