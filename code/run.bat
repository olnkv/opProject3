git clone https://github.com/google/googletest.git
mkdir build
cd build
cmake -G "MinGW Makefiles" -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ ../
cmake --build .
Tests\testout.exe