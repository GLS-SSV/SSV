@echo off
pause

:set HAL2CPP=..\HALS2CPP\Debug\HALS2CPP.exe
set HAL2CPP=..\HALS2CPP\Release\HALS2CPP.exe

set HAL=..\OV\dps\COMPOOL.hals
set CPP=..\OV\dps\COMPOOL.h

%HAL2CPP% %HAL% %CPP%

pause
@echo on
