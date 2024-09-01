#!/bin/bash

if [ -d build ]; then
    rm -rf build
fi

if [ -d install ]; then
    rm -rf install
fi

mkdir build
cd build

# if [ "$1" == "-ntest" ]; then
#         NOTEST=1
# fi

cmake -DBUILD_TEST=OFF .. && make && cmake --install .

# if [ "$NOTEST" == "1" ]; then
#     exit
# fi
cmake -DBUILD_TEST=ON .. && make && cmake --install .
