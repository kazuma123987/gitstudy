cmake_minimum_required(VERSION 3.12)
project(demo
VERSION 0.0.1
LANGUAGES C CXX)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
#全局包含目录
include_directories(${CMAKE_SOURCE_DIR}/include)
#全局包含库目录(指定库的搜索路径)
link_directories(${CMAKE_SOURCE_DIR}/lib)
#源文件
file(GLOB chess ${CMAKE_SOURCE_DIR}/src/chess/*.c)
file(GLOB guessNumber ${CMAKE_SOURCE_DIR}/src/guessNumber/*.c)
file(GLOB studentSystem ${CMAKE_SOURCE_DIR}/src/studentSystem/*.c)
file(GLOB swap ${CMAKE_SOURCE_DIR}/src/swap/*.c)
file(GLOB test ${CMAKE_SOURCE_DIR}/src/test/*.c)
#可执行文件
add_executable(chess ${chess})

add_executable(guessNumber ${guessNumber})

add_executable(studentSystem ${studentSystem})
target_include_directories(studentSystem PUBLIC "${CMAKE_SOURCE_DIR}/src/studentSystem")

add_executable(swap ${swap})
target_include_directories(swap PUBLIC "${CMAKE_SOURCE_DIR}/src/swap")

add_executable(test ${test})
target_include_directories(test PUBLIC "${CMAKE_SOURCE_DIR}/src/test")