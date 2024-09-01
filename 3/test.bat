@echo off

set current_dir=%cd%

if "%1"=="msvc" (
    call build.bat msvc
) else if "%1"=="mingw" (
    call build.bat mingw
)

if %ERRORLEVEL% NEQ 0 (
    exit /b %ERRORLEVEL%
)

cd %current_dir%/install/test
echo.
echo running shared_test:
shared_test
echo.
echo running static_test:
static_test
echo.
