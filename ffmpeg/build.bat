@echo off
cls
if not exist build (
    mkdir build
)
cd build || exit
del "./*" --recurse
cmake -G "MinGW Makefiles" -DCMAKE_TOOLCHAIN_FILE="../scripts/settings.cmake" -DCMAKE_BUILD_TYPE=%1 ..
cmake --build . -j --target=main