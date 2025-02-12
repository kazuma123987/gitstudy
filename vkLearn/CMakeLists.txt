cmake_minimum_required(VERSION 3.12)
project(
  demo
  VERSION 0.0.1
  LANGUAGES C CXX)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
set(ENV{VULKAN_SDK} ${CMAKE_SOURCE_DIR}/src/vk_sdks)

# 全局包含目录
include_directories(${CMAKE_SOURCE_DIR}/include)

# 全局包含库目录(指定库的搜索路径)
link_directories(${CMAKE_SOURCE_DIR}/lib)

# 源文件
file(GLOB vksrc ${CMAKE_SOURCE_DIR}/src/*.c*)

# 找到库
find_package(Vulkan REQUIRED)

# 可执行文件
add_executable(vksrc ${vksrc})

# 链接头文件
target_include_directories(vksrc PUBLIC ${Vulkan_INCLUDE_DIRS})

# 链接库目录
target_link_directories(vksrc PRIVATE ${CMAKE_SOURCE_DIR}/lib/glfw)

# 链接库
target_link_libraries(vksrc PRIVATE glfw3 Vulkan::Vulkan)
