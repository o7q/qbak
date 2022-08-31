@echo off
color a

:: dev
del "qbak.exe" /f 2> nul
del "qbak_reset.bat" /f 2> nul
rmdir "qbackups" /s /q 2> nul
rmdir ".vscode" /s /q 2> nul

:: build
del "..\..\..\PackagedBuild\qbak\qbak.exe" /f 2> nul
del "..\..\..\PackagedBuild\qbak\qbak_reset.bat" /f 2> nul
rmdir "..\..\..\PackagedBuild\qbak\qbackups" /s /q 2> nul

echo.
pause