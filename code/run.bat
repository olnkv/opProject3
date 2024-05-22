@echo off
mkdir build
cd build
cmake -G "Ninja" -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ ../
cmake --build .
cls
Debug\opProject.exe