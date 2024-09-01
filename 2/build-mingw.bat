
IF NOT EXIST build (
    mkdir build
)

cd build

IF NOT EXIST ../install (
    cmake -G "MinGW Makefiles" -DBUILD_TEST=OFF ..
    mingw32-make
    cmake --install .
)

cmake -G "MinGW Makefiles" -DBUILD_TEST=ON ..
mingw32-make
cmake --install .
