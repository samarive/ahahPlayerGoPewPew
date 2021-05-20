@echo off
cd ../
g++ src/*.cpp -o output.exe -I%SFMLI% -L%SFMLL% -lsfml-network -lsfml-graphics -lsfml-window -lsfml-system && output.exe