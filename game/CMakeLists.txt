cmake_minimum_required(VERSION 3.12)
#设置编译器路径
set(CMAKE_C_COMPILER C:/MinGW64/13.2.0/bin/gcc.exe)
set(CMAKE_CXX_COMPILER C:/MinGW64/13.2.0/bin/g++.exe)
#设置编译器版本
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 99)

#-Wall:开启所有警告 
#-fmessage-length=0:禁止警告信息换行 
#-ffunction-sections&&-fdata-sections:函数和数据放在单独的节(section)上
#-fno-exceptions:g++专用编译选项,不会对异常进行处理,直接打印错误信息
#-mwindows:隐藏控制台
set(COMMON_FLAG "-fmessage-length=0 -ffunction-sections -fdata-sections -fno-exceptions")
set(CMAKE_CXX_FLAGS_RELEASE "${COMMON_FLAG} -Os -mwindows")
set(CMAKE_CXX_FLAGS_DEBUG "${COMMON_FLAG} -O0 -g -Wall")
set(CMAKE_CXX_FLAGS_MINSIZEREL "$-Os -mwindows")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${COMMON_FLAG} -Os -g")

set(CMAKE_C_FLAGS_RELEASE "${COMMON_FLAG} -Os -mwindows")
set(CMAKE_C_FLAGS_DEBUG "${COMMON_FLAG} -O0 -g -Wall")
set(CMAKE_C_FLAGS_MINSIZEREL "$-Os -mwindows")
set(CMAKE_C_FLAGS_RELWITHDEBINFO "${COMMON_FLAG} -Os -g")
#set (FLAGS_TYPE CMAKE_CXX_FLAGS_${CMAKE_BUILD_TYPE})
message(STATUS "**${CMAKE_BUILD_TYPE}**")

if("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
  message(STATUS "**C:${CMAKE_C_FLAGS_RELEASE}**\n-- **C++:${CMAKE_CXX_FLAGS_RELEASE}**")

elseif("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
  message(STATUS "**C:${CMAKE_C_FLAGS_DEBUG}**\n-- **C++:${CMAKE_CXX_FLAGS_DEBUG}**")

elseif("${CMAKE_BUILD_TYPE}" STREQUAL "RelWithDebInfo")
  message(STATUS "**C:${CMAKE_C_FLAGS_RELWITHDEBINFO}**\n-- **C++:${CMAKE_CXX_FLAGS_RELWITHDEBINFO}**")

elseif("${CMAKE_BUILD_TYPE}" STREQUAL "MinSizeRel")
  message(STATUS "**C:${CMAKE_C_FLAGS_MINSIZEREL}**\n-- **C++:${CMAKE_CXX_FLAGS_MINSIZEREL}**")
  
endif()
#设置项目名和输出目录
project(main 
VERSION 0.0.1
LANGUAGES C CXX)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
# 设置头文件目录(如果设置为源目录程序将改为#include "include/GLFW/glfw3.h")
include_directories(${CMAKE_SOURCE_DIR}/include/tools ${CMAKE_SOURCE_DIR}/include/user)
# 添加源文件
set(GLAD "${CMAKE_SOURCE_DIR}/src/tools/glad/glad.c")
file(GLOB SOURCES "${CMAKE_SOURCE_DIR}/src/user/*.cpp")

if("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
# 设置版本、文件说明、文件名称、版权信息(自定义部分)
  set(VERSION_MAJOR 0)
  set(VERSION_MINOR 0)
  set(VERSION_PATCH 0)
  set(VERSION_BUILD 1)
  set(FILE_DESCRIPTION "my game demo")
  set(PRODUCT_NAME "game")
  set(COPYRIGHT "Copyright (C) 2023")
  #把工作目录下的version.rc.in编译到build目录下的version.rc
  configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/res/icon/version.rc.in
    ${CMAKE_CURRENT_BINARY_DIR}/version.rc
    @ONLY)
  add_executable(${PROJECT_NAME} ${SOURCES} ${GLAD} ${CMAKE_CURRENT_BINARY_DIR}/version.rc)# 添加可执行文件
else()
  add_executable(${PROJECT_NAME} ${SOURCES} ${GLAD})# 添加可执行文件
endif()

# 链接 FMOD 和 GLFW 库（根据需要修改库文件的路径）
if("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
  target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/fmodL.dll)
else()
  target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/fmod.dll)
endif()
target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/lib/libglfw3.a)
target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/lib/libfreetype.a)
