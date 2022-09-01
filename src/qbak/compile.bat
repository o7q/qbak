@echo off
color a
g++ *.cpp -Wall -O2 -o "qbak.exe" -static-libstdc++ -static-libgcc
echo.
pause