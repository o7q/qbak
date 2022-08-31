@echo off
color a
del "qbak.exe" /f 2> nul
del "qbak_reset.bat" /f 2> nul
rmdir "qbackups" /s /q 2> nul
rmdir ".vscode" /s /q 2> nul
echo.
pause