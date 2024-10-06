cmake_minimum_required(VERSION 3.12)
project(
  demo
  VERSION 0.0.1
  LANGUAGES C CXX)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

# 全局包含目录
include_directories(${CMAKE_SOURCE_DIR}/third_parts/asio)

# 全局包含库目录(指定库的搜索路径)
link_directories(${CMAKE_SOURCE_DIR}/lib)

# 源文件
# file(GLOB server ${CMAKE_SOURCE_DIR}/app/server/*.c ${CMAKE_SOURCE_DIR}/app/server/*.cpp)
# file(GLOB client ${CMAKE_SOURCE_DIR}/app/client/*.c ${CMAKE_SOURCE_DIR}/app/client/*.cpp)
set(server ${CMAKE_SOURCE_DIR}/app/chat/chat_server.cpp)
set(client ${CMAKE_SOURCE_DIR}/app/chat/chat_client.cpp)

# 全局链接库
if(WIN32)
  link_libraries(ws2_32 wsock32)
elseif(UNIX)
  link_libraries(pthread)
elseif(APPLE)
elseif(ANDROID)
endif()

# 可执行文件
add_executable(server ${server})
add_executable(client ${client})
