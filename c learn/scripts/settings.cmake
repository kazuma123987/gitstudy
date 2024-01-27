option(USE_GCC "if set on,cmake will use gcc,else clang will be choosed")
set(USE_GCC ON)
# 设置编译器路径
if(USE_GCC)
  set(CMAKE_C_COMPILER gcc.exe)
  set(CMAKE_CXX_COMPILER g++.exe)
else()
  set(CMAKE_C_COMPILER clang.exe)
  set(CMAKE_CXX_COMPILER clang++.exe)
endif()
# 设置C/C++版本
set(C_STANDARD 99)
set(CXX_STANDARD 11)

# -Wall:开启所有警告 -fmessage-length=0:禁止警告信息换行
# -ffunction-sections&&-fdata-sections:函数和数据放在单独的节(section)上
# -fno-exceptions:g++专用编译选项,不会对异常进行处理,直接打印错误信息 -mwindows:隐藏控制台 set(COMMON_FLAG
# "-fmessage-length=0 -ffunction-sections -fdata-sections -fno-exceptions")
if(USE_GCC)
  set(CMAKE_CXX_FLAGS_RELEASE "${COMMON_FLAG} -Os -mwindows")
  set(CMAKE_CXX_FLAGS_DEBUG "${COMMON_FLAG} -O0 -g -Wall")
  set(CMAKE_CXX_FLAGS_MINSIZEREL "$-Os -mwindows")
  set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "${COMMON_FLAG} -Os -g")

  set(CMAKE_C_FLAGS_RELEASE "${COMMON_FLAG} -Os -mwindows")
  set(CMAKE_C_FLAGS_DEBUG "${COMMON_FLAG} -O0 -g -Wall")
  set(CMAKE_C_FLAGS_MINSIZEREL "$-Os -mwindows")
  set(CMAKE_C_FLAGS_RELWITHDEBINFO "${COMMON_FLAG} -Os -g")
endif()
message(STATUS "**${CMAKE_BUILD_TYPE}**")

if("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
  message(
    STATUS
      "**C:${CMAKE_C_FLAGS_RELEASE}**\n-- **C++:${CMAKE_CXX_FLAGS_RELEASE}**")

elseif("${CMAKE_BUILD_TYPE}" STREQUAL "Debug")
  message(
    STATUS "**C:${CMAKE_C_FLAGS_DEBUG}**\n-- **C++:${CMAKE_CXX_FLAGS_DEBUG}**")

elseif("${CMAKE_BUILD_TYPE}" STREQUAL "RelWithDebInfo")
  message(
    STATUS
      "**C:${CMAKE_C_FLAGS_RELWITHDEBINFO}**\n-- **C++:${CMAKE_CXX_FLAGS_RELWITHDEBINFO}**"
  )

elseif("${CMAKE_BUILD_TYPE}" STREQUAL "MinSizeRel")
  message(
    STATUS
      "**C:${CMAKE_C_FLAGS_MINSIZEREL}**\n-- **C++:${CMAKE_CXX_FLAGS_MINSIZEREL}**"
  )

endif()
