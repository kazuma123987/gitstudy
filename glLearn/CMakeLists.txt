cmake_minimum_required(VERSION 3.12)
#设置编译器路径
set(CMAKE_C_COMPILER C:/MinGW64/13.2.0/bin/gcc.exe)
set(CMAKE_CXX_COMPILER C:/MinGW64/13.2.0/bin/g++.exe)
#设置编译器版本
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 99)

#设置编译器选项(被注释的三行是复杂的写法)
#if("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Os -fno-exceptions -mwindows")
#endif()
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
set (FLAGS_TYPE CMAKE_CXX_FLAGS_${CMAKE_BUILD_TYPE})
message(STATUS "**${CMAKE_BUILD_TYPE}**")
if("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
  message(STATUS "**${CMAKE_CXX_FLAGS_RELEASE}**")
elseif("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
  message(STATUS "**${CMAKE_CXX_FLAGS_DEBUG}**")
elseif("${CMAKE_BUILD_TYPE}" STREQUAL "RelWithDebInfo")
  message(STATUS "**${CMAKE_CXX_FLAGS_RELWITHDEBINFO}**")
elseif("${CMAKE_BUILD_TYPE}" STREQUAL "MinSizeRel")
  message(STATUS "**${CMAKE_CXX_FLAGS_MINSIZEREL}**")
endif()
#设置项目名和输出目录
project(main 
VERSION 0.0.1
LANGUAGES CXX)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
# 设置头文件目录(如果设置为源目录程序将改为#include "include/GLFW/glfw3.h")
include_directories(include)
# 添加源文件
set(SOURCES 
    src/sound.cpp
    src/shader.cpp
    src/global.cpp
    src/stb_image.cpp
    main.cpp
)
link_directories(${PROJECT_SOURCE_DIR})

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
  ${CMAKE_CURRENT_SOURCE_DIR}/version.rc.in
  ${CMAKE_CURRENT_BINARY_DIR}/version.rc
  @ONLY)
add_executable(${PROJECT_NAME} ${SOURCES} ${CMAKE_CURRENT_BINARY_DIR}/version.rc)# 添加可执行文件
else()
add_executable(${PROJECT_NAME} ${SOURCES})# 添加可执行文件
endif()

# 链接 FMOD 和 GLFW 库（根据需要修改库文件的路径）
IF("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/fmodL.dll)
ELSE()
target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/fmod.dll)
ENDIF()
#target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/GLFW/glfw3.dll)
target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include/lib/libglfw3.a)
target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include/lib/libglad.lib)