@echo off
pause

:set HALS2CPP=..\HALS2CPP\Debug\HALS2CPP.exe
set HALS2CPP=..\HALS2CPP\Release\HALS2CPP.exe

set HALS=..\OV\dps\COMPOOL.hals
set CPP=..\OV\dps\COMPOOL.h

%HALS2CPP% %HALS% %CPP%

pause
@echo on
