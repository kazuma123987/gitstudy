cmake_minimum_required(VERSION 3.12)
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
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_STANDARD 99)
project(main CXX)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})
# 设置头文件目录(这里设置project最后运行的目录是因为
#include "fmod/fmod.h"
#include "glad/glad.h" 
#include "GLFW/glfw3.h" 
#在根目录下就能找到文件夹fmod,glad,GLFW了)
include_directories(include ${PROJECT_SOURCE_DIR})
# 添加源文件
set(SOURCES 
    src/sound.cpp
    src/shader.cpp
    src/global.cpp
    main.cpp
)
link_directories(${PROJECT_SOURCE_DIR})
# 添加可执行文件
add_executable(${PROJECT_NAME} ${SOURCES} ${CMAKE_CURRENT_BINARY_DIR}/version.rc)
# 链接 FMOD 和 GLFW 库（根据需要修改库文件的路径）
IF("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/fmodL.dll)
ELSE()
target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/fmod.dll)
ENDIF()
#target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/GLFW/glfw3.dll)
target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include/lib/libglfw3.a)
target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include/lib/libglad.lib)