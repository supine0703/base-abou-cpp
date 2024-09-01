#!/bin/sh

if [ ! -d "build" ]; then
    mkdir build
fi

cd build

if [ ! -d "../install" ]; then
    cmake -DBUILD_TEST=OFF ..
    make
    cmake --install .
fi

cmake -DBUILD_TEST=ON ..
make
cmake --install .

