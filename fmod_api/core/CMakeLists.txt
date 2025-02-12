cmake_minimum_required(VERSION 3.12)
project(
  demo
  VERSION 0.0.1
  LANGUAGES C CXX)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# 全局包含目录
include_directories(${CMAKE_SOURCE_DIR}/inc)

# 全局包含库目录(指定库的搜索路径)
link_directories(${CMAKE_SOURCE_DIR}/lib/x64)

# 源文件
set(COMM_SRC
  ${CMAKE_SOURCE_DIR}/examples/common.cpp
  ${CMAKE_SOURCE_DIR}/examples/common_platform.cpp)

link_libraries(fmod_vc)

# 可执行文件
add_executable(play_stream WIN32 ${CMAKE_SOURCE_DIR}/examples/play_stream.cpp ${COMM_SRC})
add_executable(3d WIN32 ${CMAKE_SOURCE_DIR}/examples/3d.cpp ${COMM_SRC})
add_executable(effects WIN32 ${CMAKE_SOURCE_DIR}/examples/effects.cpp ${COMM_SRC})
