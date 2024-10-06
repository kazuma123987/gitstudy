set(USE_GCC ON)
set(USE_CLANG OFF)

# 设置编译器路径
if(USE_GCC)
  set(CMAKE_C_COMPILER gcc)
  set(CMAKE_CXX_COMPILER g++)
elseif(USE_CLANG)
  set(CMAKE_C_COMPILER clang)
  set(CMAKE_CXX_COMPILER clang++)
endif()

# -Wall:开启所有警告 -fmessage-length=0:禁止警告信息换行
# -ffunction-sections&&-fdata-sections:函数和数据放在单独的节(section)上
# -fno-exceptions:g++专用编译选项,不会对异常进行处理,直接打印错误信息 -mwindows:隐藏控制台 set(COMMON_FLAG
# "-fmessage-length=0 -ffunction-sections -fdata-sections -fno-exceptions")
if(USE_GCC)
  set(CMAKE_C_FLAGS "-std=c99 -fmessage-length=0 -ffunction-sections -fdata-sections")
  set(CMAKE_C_FLAGS_RELEASE "-Os -mwindows")
  set(CMAKE_C_FLAGS_DEBUG "-O0 -g -Wall")
  set(CMAKE_C_FLAGS_MINSIZEREL "-Os -mwindows")
  set(CMAKE_C_FLAGS_RELWITHDEBINFO "-Os -g")

  set(CMAKE_CXX_FLAGS "-std=c++14 -fmessage-length=0 -ffunction-sections -fdata-sections")
  set(CMAKE_CXX_FLAGS_RELEASE ${CMAKE_C_FLAGS_RELEASE})
  set(CMAKE_CXX_FLAGS_DEBUG ${CMAKE_C_FLAGS_DEBUG})
  set(CMAKE_CXX_FLAGS_MINSIZEREL ${CMAKE_C_FLAGS_MINSIZEREL})
  set(CMAKE_CXX_FLAGS_RELWITHDEBINFO ${CMAKE_C_FLAGS_RELWITHDEBINFO})
elseif(USE_CLANG)
  set(CMAKE_C_FLAGS "-std=c99 ${CMAKE_C_FLAGS}")
  set(CMAKE_CXX_FLAGS "-std=c++14 ${CMAKE_CXX_FLAGS}")
endif()

message(STATUS "**${CMAKE_BUILD_TYPE}**")

if("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
  message(STATUS "**C:${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_RELEASE}**\n-- **C++:${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE}**")

elseif("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
  message(STATUS "**C:${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_DEBUG}**\n-- **C++:${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG}**")

elseif("${CMAKE_BUILD_TYPE}" STREQUAL "RelWithDebInfo")
  message(STATUS "**C:${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_RELWITHDEBINFO}**\n-- **C++:${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELWITHDEBINFO}**")

elseif("${CMAKE_BUILD_TYPE}" STREQUAL "MinSizeRel")
  message(STATUS "**C:${CMAKE_C_FLAGS} ${CMAKE_C_FLAGS_MINSIZEREL}**\n-- **C++:${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_MINSIZEREL}**")

endif()
