
IF NOT EXIST build (
    mkdir build
)

cd build

IF NOT EXIST ../install (
    cmake -G "Visual Studio 17 2022" -DBUILD_TEST=OFF ..
    cmake --build . --config Release 
    cmake --install .
)

cmake -G "Visual Studio 17 2022" -DBUILD_TEST=ON ..
cmake --build . --config Release
cmake --install .
