@echo off
g++ -std=c++17 -O2 -Wall -Wextra src\main.cpp -o main.exe || exit /b 1
main.exe
