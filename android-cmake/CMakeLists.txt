# Sets the minimum CMake version required for this project.
cmake_minimum_required(VERSION 3.22.1)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

project(demo
        LANGUAGES C CXX
        VERSION 0.0.1)

include_directories(${CMAKE_SOURCE_DIR}/third_part)

file(GLOB hello_world ${CMAKE_SOURCE_DIR}/apps/hello_world/*.cpp)
file(GLOB android_log ${CMAKE_SOURCE_DIR}/apps/android_log/*.cpp)
file(GLOB gles_draw ${CMAKE_SOURCE_DIR}/apps/gles_draw/*.cpp)
add_executable(hello_world ${hello_world})
add_executable(android_log ${android_log})
add_executable(gles_draw ${gles_draw})

target_link_libraries(android_log

        # 链接log库就可以使用__android_log_print函数了
        android
        log)
target_link_libraries(gles_draw android log GLESv2 egl)