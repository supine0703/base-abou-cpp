@echo off

if exist build (
    rmdir /s /q build
)

if exist install (
    rmdir /s /q install
)

mkdir build
cd build

if "%1"=="msvc" (
    if "%2" == "-ntest" (
        set NOTEST=1
    )
    goto msvc
) else if "%1"=="mingw" (
    if "%2" == "-ntest" (
        set NOTEST=1
    )
    goto mingw
) else if "%1" == "-ntest" (
    set NOTEST=1
) else if "%1"=="" (
    goto mingw
) else (
    echo "Invalid argument"
    exit 1
)

:mingw
set CMAKE_G="MinGW Makefiles"
cmake -G %CMAKE_G% -DBUILD_TEST=OFF .. && (
    mingw32-make && cmake --install . && (
        if "%NOTEST%"=="1" (
            goto :eof
        )
        cmake -G %CMAKE_G% -DBUILD_TEST=ON .. && (
            mingw32-make && cmake --install .
        )
    )
)
goto :eof

:msvc
set CMAKE_G="Visual Studio 17 2022"
cmake -G %CMAKE_G% -DBUILD_TEST=OFF .. && (
    cmake --build . --config Release && cmake --install . && (
        if "%NOTEST%"=="1" (
            goto :eof
        )
        cmake -G %CMAKE_G% -DBUILD_TEST=ON .. && (
            cmake --build . --config Release && cmake --install .
        )
    )
)
goto :eof
