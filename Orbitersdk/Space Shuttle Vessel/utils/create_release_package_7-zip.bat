@echo off

set SEVENZIP_DIR="C:\Program Files\7-Zip\7z.exe"

echo input major version number:
set /P "MAJOR_VERSION="

echo input minor version number:
set /P "MINOR_VERSION="

cls

set OUTPUT_NAME=SpaceShuttleVessel_v%MAJOR_VERSION%.%MINOR_VERSION%.zip

echo creating %OUTPUT_NAME% in orbiter base directory...

cd ..\..\..

%SEVENZIP_DIR% a -tzip -mx9 %OUTPUT_NAME% "@Orbitersdk\Space Shuttle Vessel\utils\releasefilelist.txt"

@echo on

pause
