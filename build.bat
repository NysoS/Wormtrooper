@echo off
if exist build (goto :clean) else (goto :build)
exit

:clean
echo -- Cleaning old files
rmdir /s /q build
goto :build

:build
mkdir build
cd build
cmake ..
echo -- Build successful
pause
