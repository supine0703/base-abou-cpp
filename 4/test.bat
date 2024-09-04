@echo off

set current_dir=%cd%

if "%1"=="msvc" (
    call build.bat msvc || exit /b %ERRORLEVEL%
) else if "%1"=="mingw" (
    call build.bat mingw || exit /b %ERRORLEVEL%
) else if "%1"=="reb" (
    cd build
    if exist Makefile (
        cmake -G "MinGW Makefiles" -DBUILD_TEST=ON .. && (
            mingw32-make && cmake --install .
        ) || exit /b %ERRORLEVEL%
    ) else (
        cmake -G "Visual Studio 17 2022" -DBUILD_TEST=ON .. && (
            cmake --build . --config Release && cmake --install .
        ) || exit /b %ERRORLEVEL%
    )
)

cd %current_dir%/install/test
echo.
echo running shared_test:
shared_test
echo.
echo running static_test:
static_test
echo.
