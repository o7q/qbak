@echo off
color a
g++ *.cpp "resources\icon\icon.res" -Wall -O2 -o "qbak.exe" -static-libstdc++ -static-libgcc
echo.
pause