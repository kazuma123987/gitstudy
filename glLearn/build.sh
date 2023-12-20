#!/bin/bash
clear
if [ ! -d "build" ]; then
  # 如果不存在，则创建 build 目录
  mkdir build
fi
cd build
rm -rf "."/*
cmake -G 'MinGW Makefiles' -DCMAKE_BUILD_TYPE=Debug ..
cmake --build . -j --target all