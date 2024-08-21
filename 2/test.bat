
IF NOT EXIST build (
    mkdir build
)
cd build
cmake -G "MinGW Makefiles" ..
make

Demo
