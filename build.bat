@echo off
set currentDir=%cd%
if exist build (goto :clean) else (goto :build)
exit

:clean
echo -- Cleaning old files
rmdir /s /q build
goto :build

:gitmodule
echo -- Update submodule
git submodule init
git submodule update
goto :vcpkg_install

:vcpkg_install
echo -- Install vcpkg
cd vendor/vcpkg
cmd /c "bootstrap-vcpkg.bat --disable-metrics"
goto :vcpkg_module

:vcpkg_module
echo -- Install vcpkg modules
cmd /c "vcpkg install"
vcpkg integrate install
cd %currentDir%
goto :build

:build
mkdir build
cd build
cmake ..
echo -- Build successful
pause