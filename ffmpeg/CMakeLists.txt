cmake_minimum_required(VERSION 3.12)
project(main
VERSION 0.0.1
LANGUAGES C CXX)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
include_directories(${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/include/ffmpeg)
set(GLAD "${CMAKE_SOURCE_DIR}/src/glad/glad.c")
file(GLOB SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES} ${GLAD})
target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/lib/ffmpeg/libavcodec.dll.a)
target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/lib/ffmpeg/libavformat.dll.a)
target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/lib/ffmpeg/libswscale.dll.a)
target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/lib/ffmpeg/libavutil.dll.a)
target_link_libraries(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/lib/libglfw3.a)