@echo off
color a
g++ *.cpp -Wall -o "..\..\..\PackagedBuild\qbak\qbak.exe" -static-libstdc++ -static-libgcc
echo.
pause