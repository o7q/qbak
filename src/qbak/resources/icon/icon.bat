@echo off
color a
windres "icon.rc" -O coff -o "icon.res"
echo.
pause