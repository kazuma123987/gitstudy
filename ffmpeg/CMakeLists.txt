cmake_minimum_required(VERSION 3.12)
project(
  main
  VERSION 0.0.1
  LANGUAGES C CXX)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR})
include_directories(
  ${CMAKE_SOURCE_DIR}/include ${CMAKE_SOURCE_DIR}/include/ffmpeg
  ${CMAKE_SOURCE_DIR}/include/utils)
link_directories(${CMAKE_SOURCE_DIR}/lib ${CMAKE_SOURCE_DIR}/lib/ffmpeg
                 ${CMAKE_SOURCE_DIR}/build)
set(GLAD "${CMAKE_SOURCE_DIR}/src/glad/glad.c")
set(UTIL ${CMAKE_SOURCE_DIR}/src/utils/util.c)
file(GLOB SOURCES "${CMAKE_SOURCE_DIR}/src/media_player/*.cpp")
link_libraries(libavcodec.dll.a libavformat.dll.a libswscale.dll.a
               libavutil.dll.a libavdevice.dll.a libswresample.dll.a)
add_library(util ${UTIL})
add_executable(media_player ${SOURCES} ${GLAD})
target_link_libraries(media_player PRIVATE libglfw3.a libSDL2.dll.a fmod_vc.lib
                                           libutil.a)
