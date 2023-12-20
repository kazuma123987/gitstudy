@echo off
cls
if not exist build (
  mkdir build
)
cd build || exit
del "./*" --recurse
cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug ..
cmake --build . -j --target all
cd ..
main.exe