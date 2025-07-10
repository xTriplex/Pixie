@echo off
REM -------------------------------------------------------------
REM generate_vs2022.bat
REM Runs Premake5 to generate a VS2022 solution for PixieEngine
REM -------------------------------------------------------------

REM 1) Move to the directory where this script lives
cd /d "%~dp0"

REM 2) Define the path to premake5.exe
set PREMAKE_EXE=Vendor\Premake\premake5.exe

REM 3) Verify it exists
if not exist "%PREMAKE_EXE%" (
    echo ERROR: "%PREMAKE_EXE%" not found.
    pause
    exit /b 1
)

REM 4) Run premake to generate VS2022 projects
echo Generating Visual Studio 2022 solution...
"%PREMAKE_EXE%" vs2022

REM 5) Check result
if errorlevel 1 (
    echo.
    echo Premake5 failed – please check for errors above.
    pause
    exit /b 1
) else (
    echo.
    echo Success! Projects generated.
    pause
    exit /b 0
)
