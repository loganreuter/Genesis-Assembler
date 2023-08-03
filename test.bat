@echo off

cmake -S . -B build

cmake --build build

echo Done Building

build\app\Debug\asm.exe test.txt