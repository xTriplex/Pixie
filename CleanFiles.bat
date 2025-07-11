@echo off
REM -------------------------------------------------------------
REM clean_and_generate.bat
REM Cleans all build artifacts and regenerates the solution
REM -------------------------------------------------------------
cd /d "%~dp0"

echo Cleaning...
rmdir /s /q bin
rmdir /s /q bin-int
del /s /q *.vcxproj *.vcxproj.filters *.sln

echo.
call GenerateVisualStudio2022Files.bat
