# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.29

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\34181\Desktop\gitstudy\glLearn

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\34181\Desktop\gitstudy\glLearn\build

# Include any dependencies generated for this target.
include CMakeFiles/main.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/main.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/main.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/main.dir/flags.make

CMakeFiles/main.dir/src/camera.cpp.obj: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/camera.cpp.obj: CMakeFiles/main.dir/includes_CXX.rsp
CMakeFiles/main.dir/src/camera.cpp.obj: C:/Users/34181/Desktop/gitstudy/glLearn/src/camera.cpp
CMakeFiles/main.dir/src/camera.cpp.obj: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\34181\Desktop\gitstudy\glLearn\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/main.dir/src/camera.cpp.obj"
	C:\A_TOOLS\MinGW64\x86_64-14.2.0-release-posix-seh-msvcrt-rt_v12-rev1\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/src/camera.cpp.obj -MF CMakeFiles\main.dir\src\camera.cpp.obj.d -o CMakeFiles\main.dir\src\camera.cpp.obj -c C:\Users\34181\Desktop\gitstudy\glLearn\src\camera.cpp

CMakeFiles/main.dir/src/camera.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/main.dir/src/camera.cpp.i"
	C:\A_TOOLS\MinGW64\x86_64-14.2.0-release-posix-seh-msvcrt-rt_v12-rev1\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\34181\Desktop\gitstudy\glLearn\src\camera.cpp > CMakeFiles\main.dir\src\camera.cpp.i

CMakeFiles/main.dir/src/camera.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/camera.cpp.s"
	C:\A_TOOLS\MinGW64\x86_64-14.2.0-release-posix-seh-msvcrt-rt_v12-rev1\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\34181\Desktop\gitstudy\glLearn\src\camera.cpp -o CMakeFiles\main.dir\src\camera.cpp.s

CMakeFiles/main.dir/src/game.cpp.obj: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/game.cpp.obj: CMakeFiles/main.dir/includes_CXX.rsp
CMakeFiles/main.dir/src/game.cpp.obj: C:/Users/34181/Desktop/gitstudy/glLearn/src/game.cpp
CMakeFiles/main.dir/src/game.cpp.obj: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\34181\Desktop\gitstudy\glLearn\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/main.dir/src/game.cpp.obj"
	C:\A_TOOLS\MinGW64\x86_64-14.2.0-release-posix-seh-msvcrt-rt_v12-rev1\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/src/game.cpp.obj -MF CMakeFiles\main.dir\src\game.cpp.obj.d -o CMakeFiles\main.dir\src\game.cpp.obj -c C:\Users\34181\Desktop\gitstudy\glLearn\src\game.cpp

CMakeFiles/main.dir/src/game.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/main.dir/src/game.cpp.i"
	C:\A_TOOLS\MinGW64\x86_64-14.2.0-release-posix-seh-msvcrt-rt_v12-rev1\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\34181\Desktop\gitstudy\glLearn\src\game.cpp > CMakeFiles\main.dir\src\game.cpp.i

CMakeFiles/main.dir/src/game.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/game.cpp.s"
	C:\A_TOOLS\MinGW64\x86_64-14.2.0-release-posix-seh-msvcrt-rt_v12-rev1\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\34181\Desktop\gitstudy\glLearn\src\game.cpp -o CMakeFiles\main.dir\src\game.cpp.s

CMakeFiles/main.dir/src/glad.c.obj: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/glad.c.obj: CMakeFiles/main.dir/includes_C.rsp
CMakeFiles/main.dir/src/glad.c.obj: C:/Users/34181/Desktop/gitstudy/glLearn/src/glad.c
CMakeFiles/main.dir/src/glad.c.obj: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\34181\Desktop\gitstudy\glLearn\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/main.dir/src/glad.c.obj"
	C:\A_TOOLS\MinGW64\x86_64-14.2.0-release-posix-seh-msvcrt-rt_v12-rev1\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/main.dir/src/glad.c.obj -MF CMakeFiles\main.dir\src\glad.c.obj.d -o CMakeFiles\main.dir\src\glad.c.obj -c C:\Users\34181\Desktop\gitstudy\glLearn\src\glad.c

CMakeFiles/main.dir/src/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/main.dir/src/glad.c.i"
	C:\A_TOOLS\MinGW64\x86_64-14.2.0-release-posix-seh-msvcrt-rt_v12-rev1\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\34181\Desktop\gitstudy\glLearn\src\glad.c > CMakeFiles\main.dir\src\glad.c.i

CMakeFiles/main.dir/src/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/main.dir/src/glad.c.s"
	C:\A_TOOLS\MinGW64\x86_64-14.2.0-release-posix-seh-msvcrt-rt_v12-rev1\mingw64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\34181\Desktop\gitstudy\glLearn\src\glad.c -o CMakeFiles\main.dir\src\glad.c.s

CMakeFiles/main.dir/src/global.cpp.obj: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/global.cpp.obj: CMakeFiles/main.dir/includes_CXX.rsp
CMakeFiles/main.dir/src/global.cpp.obj: C:/Users/34181/Desktop/gitstudy/glLearn/src/global.cpp
CMakeFiles/main.dir/src/global.cpp.obj: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\34181\Desktop\gitstudy\glLearn\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/main.dir/src/global.cpp.obj"
	C:\A_TOOLS\MinGW64\x86_64-14.2.0-release-posix-seh-msvcrt-rt_v12-rev1\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/src/global.cpp.obj -MF CMakeFiles\main.dir\src\global.cpp.obj.d -o CMakeFiles\main.dir\src\global.cpp.obj -c C:\Users\34181\Desktop\gitstudy\glLearn\src\global.cpp

CMakeFiles/main.dir/src/global.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/main.dir/src/global.cpp.i"
	C:\A_TOOLS\MinGW64\x86_64-14.2.0-release-posix-seh-msvcrt-rt_v12-rev1\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\34181\Desktop\gitstudy\glLearn\src\global.cpp > CMakeFiles\main.dir\src\global.cpp.i

CMakeFiles/main.dir/src/global.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/global.cpp.s"
	C:\A_TOOLS\MinGW64\x86_64-14.2.0-release-posix-seh-msvcrt-rt_v12-rev1\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\34181\Desktop\gitstudy\glLearn\src\global.cpp -o CMakeFiles\main.dir\src\global.cpp.s

CMakeFiles/main.dir/src/main.cpp.obj: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/main.cpp.obj: CMakeFiles/main.dir/includes_CXX.rsp
CMakeFiles/main.dir/src/main.cpp.obj: C:/Users/34181/Desktop/gitstudy/glLearn/src/main.cpp
CMakeFiles/main.dir/src/main.cpp.obj: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\34181\Desktop\gitstudy\glLearn\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/main.dir/src/main.cpp.obj"
	C:\A_TOOLS\MinGW64\x86_64-14.2.0-release-posix-seh-msvcrt-rt_v12-rev1\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/src/main.cpp.obj -MF CMakeFiles\main.dir\src\main.cpp.obj.d -o CMakeFiles\main.dir\src\main.cpp.obj -c C:\Users\34181\Desktop\gitstudy\glLearn\src\main.cpp

CMakeFiles/main.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/main.dir/src/main.cpp.i"
	C:\A_TOOLS\MinGW64\x86_64-14.2.0-release-posix-seh-msvcrt-rt_v12-rev1\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\34181\Desktop\gitstudy\glLearn\src\main.cpp > CMakeFiles\main.dir\src\main.cpp.i

CMakeFiles/main.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/main.cpp.s"
	C:\A_TOOLS\MinGW64\x86_64-14.2.0-release-posix-seh-msvcrt-rt_v12-rev1\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\34181\Desktop\gitstudy\glLearn\src\main.cpp -o CMakeFiles\main.dir\src\main.cpp.s

CMakeFiles/main.dir/src/mesh.cpp.obj: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/mesh.cpp.obj: CMakeFiles/main.dir/includes_CXX.rsp
CMakeFiles/main.dir/src/mesh.cpp.obj: C:/Users/34181/Desktop/gitstudy/glLearn/src/mesh.cpp
CMakeFiles/main.dir/src/mesh.cpp.obj: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\34181\Desktop\gitstudy\glLearn\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/main.dir/src/mesh.cpp.obj"
	C:\A_TOOLS\MinGW64\x86_64-14.2.0-release-posix-seh-msvcrt-rt_v12-rev1\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/src/mesh.cpp.obj -MF CMakeFiles\main.dir\src\mesh.cpp.obj.d -o CMakeFiles\main.dir\src\mesh.cpp.obj -c C:\Users\34181\Desktop\gitstudy\glLearn\src\mesh.cpp

CMakeFiles/main.dir/src/mesh.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/main.dir/src/mesh.cpp.i"
	C:\A_TOOLS\MinGW64\x86_64-14.2.0-release-posix-seh-msvcrt-rt_v12-rev1\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\34181\Desktop\gitstudy\glLearn\src\mesh.cpp > CMakeFiles\main.dir\src\mesh.cpp.i

CMakeFiles/main.dir/src/mesh.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/mesh.cpp.s"
	C:\A_TOOLS\MinGW64\x86_64-14.2.0-release-posix-seh-msvcrt-rt_v12-rev1\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\34181\Desktop\gitstudy\glLearn\src\mesh.cpp -o CMakeFiles\main.dir\src\mesh.cpp.s

CMakeFiles/main.dir/src/model.cpp.obj: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/model.cpp.obj: CMakeFiles/main.dir/includes_CXX.rsp
CMakeFiles/main.dir/src/model.cpp.obj: C:/Users/34181/Desktop/gitstudy/glLearn/src/model.cpp
CMakeFiles/main.dir/src/model.cpp.obj: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\34181\Desktop\gitstudy\glLearn\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/main.dir/src/model.cpp.obj"
	C:\A_TOOLS\MinGW64\x86_64-14.2.0-release-posix-seh-msvcrt-rt_v12-rev1\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/src/model.cpp.obj -MF CMakeFiles\main.dir\src\model.cpp.obj.d -o CMakeFiles\main.dir\src\model.cpp.obj -c C:\Users\34181\Desktop\gitstudy\glLearn\src\model.cpp

CMakeFiles/main.dir/src/model.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/main.dir/src/model.cpp.i"
	C:\A_TOOLS\MinGW64\x86_64-14.2.0-release-posix-seh-msvcrt-rt_v12-rev1\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\34181\Desktop\gitstudy\glLearn\src\model.cpp > CMakeFiles\main.dir\src\model.cpp.i

CMakeFiles/main.dir/src/model.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/model.cpp.s"
	C:\A_TOOLS\MinGW64\x86_64-14.2.0-release-posix-seh-msvcrt-rt_v12-rev1\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\34181\Desktop\gitstudy\glLearn\src\model.cpp -o CMakeFiles\main.dir\src\model.cpp.s

CMakeFiles/main.dir/src/shader.cpp.obj: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/shader.cpp.obj: CMakeFiles/main.dir/includes_CXX.rsp
CMakeFiles/main.dir/src/shader.cpp.obj: C:/Users/34181/Desktop/gitstudy/glLearn/src/shader.cpp
CMakeFiles/main.dir/src/shader.cpp.obj: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\34181\Desktop\gitstudy\glLearn\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/main.dir/src/shader.cpp.obj"
	C:\A_TOOLS\MinGW64\x86_64-14.2.0-release-posix-seh-msvcrt-rt_v12-rev1\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/src/shader.cpp.obj -MF CMakeFiles\main.dir\src\shader.cpp.obj.d -o CMakeFiles\main.dir\src\shader.cpp.obj -c C:\Users\34181\Desktop\gitstudy\glLearn\src\shader.cpp

CMakeFiles/main.dir/src/shader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/main.dir/src/shader.cpp.i"
	C:\A_TOOLS\MinGW64\x86_64-14.2.0-release-posix-seh-msvcrt-rt_v12-rev1\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\34181\Desktop\gitstudy\glLearn\src\shader.cpp > CMakeFiles\main.dir\src\shader.cpp.i

CMakeFiles/main.dir/src/shader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/shader.cpp.s"
	C:\A_TOOLS\MinGW64\x86_64-14.2.0-release-posix-seh-msvcrt-rt_v12-rev1\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\34181\Desktop\gitstudy\glLearn\src\shader.cpp -o CMakeFiles\main.dir\src\shader.cpp.s

CMakeFiles/main.dir/src/sound.cpp.obj: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/sound.cpp.obj: CMakeFiles/main.dir/includes_CXX.rsp
CMakeFiles/main.dir/src/sound.cpp.obj: C:/Users/34181/Desktop/gitstudy/glLearn/src/sound.cpp
CMakeFiles/main.dir/src/sound.cpp.obj: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\34181\Desktop\gitstudy\glLearn\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/main.dir/src/sound.cpp.obj"
	C:\A_TOOLS\MinGW64\x86_64-14.2.0-release-posix-seh-msvcrt-rt_v12-rev1\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/src/sound.cpp.obj -MF CMakeFiles\main.dir\src\sound.cpp.obj.d -o CMakeFiles\main.dir\src\sound.cpp.obj -c C:\Users\34181\Desktop\gitstudy\glLearn\src\sound.cpp

CMakeFiles/main.dir/src/sound.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/main.dir/src/sound.cpp.i"
	C:\A_TOOLS\MinGW64\x86_64-14.2.0-release-posix-seh-msvcrt-rt_v12-rev1\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\34181\Desktop\gitstudy\glLearn\src\sound.cpp > CMakeFiles\main.dir\src\sound.cpp.i

CMakeFiles/main.dir/src/sound.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/sound.cpp.s"
	C:\A_TOOLS\MinGW64\x86_64-14.2.0-release-posix-seh-msvcrt-rt_v12-rev1\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\34181\Desktop\gitstudy\glLearn\src\sound.cpp -o CMakeFiles\main.dir\src\sound.cpp.s

CMakeFiles/main.dir/src/stb_image.cpp.obj: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/stb_image.cpp.obj: CMakeFiles/main.dir/includes_CXX.rsp
CMakeFiles/main.dir/src/stb_image.cpp.obj: C:/Users/34181/Desktop/gitstudy/glLearn/src/stb_image.cpp
CMakeFiles/main.dir/src/stb_image.cpp.obj: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\34181\Desktop\gitstudy\glLearn\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/main.dir/src/stb_image.cpp.obj"
	C:\A_TOOLS\MinGW64\x86_64-14.2.0-release-posix-seh-msvcrt-rt_v12-rev1\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/src/stb_image.cpp.obj -MF CMakeFiles\main.dir\src\stb_image.cpp.obj.d -o CMakeFiles\main.dir\src\stb_image.cpp.obj -c C:\Users\34181\Desktop\gitstudy\glLearn\src\stb_image.cpp

CMakeFiles/main.dir/src/stb_image.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/main.dir/src/stb_image.cpp.i"
	C:\A_TOOLS\MinGW64\x86_64-14.2.0-release-posix-seh-msvcrt-rt_v12-rev1\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\34181\Desktop\gitstudy\glLearn\src\stb_image.cpp > CMakeFiles\main.dir\src\stb_image.cpp.i

CMakeFiles/main.dir/src/stb_image.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/stb_image.cpp.s"
	C:\A_TOOLS\MinGW64\x86_64-14.2.0-release-posix-seh-msvcrt-rt_v12-rev1\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\34181\Desktop\gitstudy\glLearn\src\stb_image.cpp -o CMakeFiles\main.dir\src\stb_image.cpp.s

CMakeFiles/main.dir/src/imgui/imgui.cpp.obj: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/imgui/imgui.cpp.obj: CMakeFiles/main.dir/includes_CXX.rsp
CMakeFiles/main.dir/src/imgui/imgui.cpp.obj: C:/Users/34181/Desktop/gitstudy/glLearn/src/imgui/imgui.cpp
CMakeFiles/main.dir/src/imgui/imgui.cpp.obj: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\34181\Desktop\gitstudy\glLearn\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Building CXX object CMakeFiles/main.dir/src/imgui/imgui.cpp.obj"
	C:\A_TOOLS\MinGW64\x86_64-14.2.0-release-posix-seh-msvcrt-rt_v12-rev1\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/src/imgui/imgui.cpp.obj -MF CMakeFiles\main.dir\src\imgui\imgui.cpp.obj.d -o CMakeFiles\main.dir\src\imgui\imgui.cpp.obj -c C:\Users\34181\Desktop\gitstudy\glLearn\src\imgui\imgui.cpp

CMakeFiles/main.dir/src/imgui/imgui.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/main.dir/src/imgui/imgui.cpp.i"
	C:\A_TOOLS\MinGW64\x86_64-14.2.0-release-posix-seh-msvcrt-rt_v12-rev1\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\34181\Desktop\gitstudy\glLearn\src\imgui\imgui.cpp > CMakeFiles\main.dir\src\imgui\imgui.cpp.i

CMakeFiles/main.dir/src/imgui/imgui.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/imgui/imgui.cpp.s"
	C:\A_TOOLS\MinGW64\x86_64-14.2.0-release-posix-seh-msvcrt-rt_v12-rev1\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\34181\Desktop\gitstudy\glLearn\src\imgui\imgui.cpp -o CMakeFiles\main.dir\src\imgui\imgui.cpp.s

CMakeFiles/main.dir/src/imgui/imgui_demo.cpp.obj: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/imgui/imgui_demo.cpp.obj: CMakeFiles/main.dir/includes_CXX.rsp
CMakeFiles/main.dir/src/imgui/imgui_demo.cpp.obj: C:/Users/34181/Desktop/gitstudy/glLearn/src/imgui/imgui_demo.cpp
CMakeFiles/main.dir/src/imgui/imgui_demo.cpp.obj: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\34181\Desktop\gitstudy\glLearn\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_12) "Building CXX object CMakeFiles/main.dir/src/imgui/imgui_demo.cpp.obj"
	C:\A_TOOLS\MinGW64\x86_64-14.2.0-release-posix-seh-msvcrt-rt_v12-rev1\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/src/imgui/imgui_demo.cpp.obj -MF CMakeFiles\main.dir\src\imgui\imgui_demo.cpp.obj.d -o CMakeFiles\main.dir\src\imgui\imgui_demo.cpp.obj -c C:\Users\34181\Desktop\gitstudy\glLearn\src\imgui\imgui_demo.cpp

CMakeFiles/main.dir/src/imgui/imgui_demo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/main.dir/src/imgui/imgui_demo.cpp.i"
	C:\A_TOOLS\MinGW64\x86_64-14.2.0-release-posix-seh-msvcrt-rt_v12-rev1\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\34181\Desktop\gitstudy\glLearn\src\imgui\imgui_demo.cpp > CMakeFiles\main.dir\src\imgui\imgui_demo.cpp.i

CMakeFiles/main.dir/src/imgui/imgui_demo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/imgui/imgui_demo.cpp.s"
	C:\A_TOOLS\MinGW64\x86_64-14.2.0-release-posix-seh-msvcrt-rt_v12-rev1\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\34181\Desktop\gitstudy\glLearn\src\imgui\imgui_demo.cpp -o CMakeFiles\main.dir\src\imgui\imgui_demo.cpp.s

CMakeFiles/main.dir/src/imgui/imgui_draw.cpp.obj: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/imgui/imgui_draw.cpp.obj: CMakeFiles/main.dir/includes_CXX.rsp
CMakeFiles/main.dir/src/imgui/imgui_draw.cpp.obj: C:/Users/34181/Desktop/gitstudy/glLearn/src/imgui/imgui_draw.cpp
CMakeFiles/main.dir/src/imgui/imgui_draw.cpp.obj: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\34181\Desktop\gitstudy\glLearn\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_13) "Building CXX object CMakeFiles/main.dir/src/imgui/imgui_draw.cpp.obj"
	C:\A_TOOLS\MinGW64\x86_64-14.2.0-release-posix-seh-msvcrt-rt_v12-rev1\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/src/imgui/imgui_draw.cpp.obj -MF CMakeFiles\main.dir\src\imgui\imgui_draw.cpp.obj.d -o CMakeFiles\main.dir\src\imgui\imgui_draw.cpp.obj -c C:\Users\34181\Desktop\gitstudy\glLearn\src\imgui\imgui_draw.cpp

CMakeFiles/main.dir/src/imgui/imgui_draw.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/main.dir/src/imgui/imgui_draw.cpp.i"
	C:\A_TOOLS\MinGW64\x86_64-14.2.0-release-posix-seh-msvcrt-rt_v12-rev1\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\34181\Desktop\gitstudy\glLearn\src\imgui\imgui_draw.cpp > CMakeFiles\main.dir\src\imgui\imgui_draw.cpp.i

CMakeFiles/main.dir/src/imgui/imgui_draw.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/imgui/imgui_draw.cpp.s"
	C:\A_TOOLS\MinGW64\x86_64-14.2.0-release-posix-seh-msvcrt-rt_v12-rev1\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\34181\Desktop\gitstudy\glLearn\src\imgui\imgui_draw.cpp -o CMakeFiles\main.dir\src\imgui\imgui_draw.cpp.s

CMakeFiles/main.dir/src/imgui/imgui_tables.cpp.obj: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/imgui/imgui_tables.cpp.obj: CMakeFiles/main.dir/includes_CXX.rsp
CMakeFiles/main.dir/src/imgui/imgui_tables.cpp.obj: C:/Users/34181/Desktop/gitstudy/glLearn/src/imgui/imgui_tables.cpp
CMakeFiles/main.dir/src/imgui/imgui_tables.cpp.obj: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\34181\Desktop\gitstudy\glLearn\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_14) "Building CXX object CMakeFiles/main.dir/src/imgui/imgui_tables.cpp.obj"
	C:\A_TOOLS\MinGW64\x86_64-14.2.0-release-posix-seh-msvcrt-rt_v12-rev1\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/src/imgui/imgui_tables.cpp.obj -MF CMakeFiles\main.dir\src\imgui\imgui_tables.cpp.obj.d -o CMakeFiles\main.dir\src\imgui\imgui_tables.cpp.obj -c C:\Users\34181\Desktop\gitstudy\glLearn\src\imgui\imgui_tables.cpp

CMakeFiles/main.dir/src/imgui/imgui_tables.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/main.dir/src/imgui/imgui_tables.cpp.i"
	C:\A_TOOLS\MinGW64\x86_64-14.2.0-release-posix-seh-msvcrt-rt_v12-rev1\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\34181\Desktop\gitstudy\glLearn\src\imgui\imgui_tables.cpp > CMakeFiles\main.dir\src\imgui\imgui_tables.cpp.i

CMakeFiles/main.dir/src/imgui/imgui_tables.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/imgui/imgui_tables.cpp.s"
	C:\A_TOOLS\MinGW64\x86_64-14.2.0-release-posix-seh-msvcrt-rt_v12-rev1\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\34181\Desktop\gitstudy\glLearn\src\imgui\imgui_tables.cpp -o CMakeFiles\main.dir\src\imgui\imgui_tables.cpp.s

CMakeFiles/main.dir/src/imgui/imgui_widgets.cpp.obj: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/imgui/imgui_widgets.cpp.obj: CMakeFiles/main.dir/includes_CXX.rsp
CMakeFiles/main.dir/src/imgui/imgui_widgets.cpp.obj: C:/Users/34181/Desktop/gitstudy/glLearn/src/imgui/imgui_widgets.cpp
CMakeFiles/main.dir/src/imgui/imgui_widgets.cpp.obj: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\34181\Desktop\gitstudy\glLearn\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_15) "Building CXX object CMakeFiles/main.dir/src/imgui/imgui_widgets.cpp.obj"
	C:\A_TOOLS\MinGW64\x86_64-14.2.0-release-posix-seh-msvcrt-rt_v12-rev1\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/src/imgui/imgui_widgets.cpp.obj -MF CMakeFiles\main.dir\src\imgui\imgui_widgets.cpp.obj.d -o CMakeFiles\main.dir\src\imgui\imgui_widgets.cpp.obj -c C:\Users\34181\Desktop\gitstudy\glLearn\src\imgui\imgui_widgets.cpp

CMakeFiles/main.dir/src/imgui/imgui_widgets.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/main.dir/src/imgui/imgui_widgets.cpp.i"
	C:\A_TOOLS\MinGW64\x86_64-14.2.0-release-posix-seh-msvcrt-rt_v12-rev1\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\34181\Desktop\gitstudy\glLearn\src\imgui\imgui_widgets.cpp > CMakeFiles\main.dir\src\imgui\imgui_widgets.cpp.i

CMakeFiles/main.dir/src/imgui/imgui_widgets.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/imgui/imgui_widgets.cpp.s"
	C:\A_TOOLS\MinGW64\x86_64-14.2.0-release-posix-seh-msvcrt-rt_v12-rev1\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\34181\Desktop\gitstudy\glLearn\src\imgui\imgui_widgets.cpp -o CMakeFiles\main.dir\src\imgui\imgui_widgets.cpp.s

CMakeFiles/main.dir/src/imgui/platform/imgui_impl_glfw.cpp.obj: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/imgui/platform/imgui_impl_glfw.cpp.obj: CMakeFiles/main.dir/includes_CXX.rsp
CMakeFiles/main.dir/src/imgui/platform/imgui_impl_glfw.cpp.obj: C:/Users/34181/Desktop/gitstudy/glLearn/src/imgui/platform/imgui_impl_glfw.cpp
CMakeFiles/main.dir/src/imgui/platform/imgui_impl_glfw.cpp.obj: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\34181\Desktop\gitstudy\glLearn\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_16) "Building CXX object CMakeFiles/main.dir/src/imgui/platform/imgui_impl_glfw.cpp.obj"
	C:\A_TOOLS\MinGW64\x86_64-14.2.0-release-posix-seh-msvcrt-rt_v12-rev1\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/src/imgui/platform/imgui_impl_glfw.cpp.obj -MF CMakeFiles\main.dir\src\imgui\platform\imgui_impl_glfw.cpp.obj.d -o CMakeFiles\main.dir\src\imgui\platform\imgui_impl_glfw.cpp.obj -c C:\Users\34181\Desktop\gitstudy\glLearn\src\imgui\platform\imgui_impl_glfw.cpp

CMakeFiles/main.dir/src/imgui/platform/imgui_impl_glfw.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/main.dir/src/imgui/platform/imgui_impl_glfw.cpp.i"
	C:\A_TOOLS\MinGW64\x86_64-14.2.0-release-posix-seh-msvcrt-rt_v12-rev1\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\34181\Desktop\gitstudy\glLearn\src\imgui\platform\imgui_impl_glfw.cpp > CMakeFiles\main.dir\src\imgui\platform\imgui_impl_glfw.cpp.i

CMakeFiles/main.dir/src/imgui/platform/imgui_impl_glfw.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/imgui/platform/imgui_impl_glfw.cpp.s"
	C:\A_TOOLS\MinGW64\x86_64-14.2.0-release-posix-seh-msvcrt-rt_v12-rev1\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\34181\Desktop\gitstudy\glLearn\src\imgui\platform\imgui_impl_glfw.cpp -o CMakeFiles\main.dir\src\imgui\platform\imgui_impl_glfw.cpp.s

CMakeFiles/main.dir/src/imgui/platform/imgui_impl_opengl3.cpp.obj: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/src/imgui/platform/imgui_impl_opengl3.cpp.obj: CMakeFiles/main.dir/includes_CXX.rsp
CMakeFiles/main.dir/src/imgui/platform/imgui_impl_opengl3.cpp.obj: C:/Users/34181/Desktop/gitstudy/glLearn/src/imgui/platform/imgui_impl_opengl3.cpp
CMakeFiles/main.dir/src/imgui/platform/imgui_impl_opengl3.cpp.obj: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\34181\Desktop\gitstudy\glLearn\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_17) "Building CXX object CMakeFiles/main.dir/src/imgui/platform/imgui_impl_opengl3.cpp.obj"
	C:\A_TOOLS\MinGW64\x86_64-14.2.0-release-posix-seh-msvcrt-rt_v12-rev1\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/src/imgui/platform/imgui_impl_opengl3.cpp.obj -MF CMakeFiles\main.dir\src\imgui\platform\imgui_impl_opengl3.cpp.obj.d -o CMakeFiles\main.dir\src\imgui\platform\imgui_impl_opengl3.cpp.obj -c C:\Users\34181\Desktop\gitstudy\glLearn\src\imgui\platform\imgui_impl_opengl3.cpp

CMakeFiles/main.dir/src/imgui/platform/imgui_impl_opengl3.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/main.dir/src/imgui/platform/imgui_impl_opengl3.cpp.i"
	C:\A_TOOLS\MinGW64\x86_64-14.2.0-release-posix-seh-msvcrt-rt_v12-rev1\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\34181\Desktop\gitstudy\glLearn\src\imgui\platform\imgui_impl_opengl3.cpp > CMakeFiles\main.dir\src\imgui\platform\imgui_impl_opengl3.cpp.i

CMakeFiles/main.dir/src/imgui/platform/imgui_impl_opengl3.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/main.dir/src/imgui/platform/imgui_impl_opengl3.cpp.s"
	C:\A_TOOLS\MinGW64\x86_64-14.2.0-release-posix-seh-msvcrt-rt_v12-rev1\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\34181\Desktop\gitstudy\glLearn\src\imgui\platform\imgui_impl_opengl3.cpp -o CMakeFiles\main.dir\src\imgui\platform\imgui_impl_opengl3.cpp.s

# Object files for target main
main_OBJECTS = \
"CMakeFiles/main.dir/src/camera.cpp.obj" \
"CMakeFiles/main.dir/src/game.cpp.obj" \
"CMakeFiles/main.dir/src/glad.c.obj" \
"CMakeFiles/main.dir/src/global.cpp.obj" \
"CMakeFiles/main.dir/src/main.cpp.obj" \
"CMakeFiles/main.dir/src/mesh.cpp.obj" \
"CMakeFiles/main.dir/src/model.cpp.obj" \
"CMakeFiles/main.dir/src/shader.cpp.obj" \
"CMakeFiles/main.dir/src/sound.cpp.obj" \
"CMakeFiles/main.dir/src/stb_image.cpp.obj" \
"CMakeFiles/main.dir/src/imgui/imgui.cpp.obj" \
"CMakeFiles/main.dir/src/imgui/imgui_demo.cpp.obj" \
"CMakeFiles/main.dir/src/imgui/imgui_draw.cpp.obj" \
"CMakeFiles/main.dir/src/imgui/imgui_tables.cpp.obj" \
"CMakeFiles/main.dir/src/imgui/imgui_widgets.cpp.obj" \
"CMakeFiles/main.dir/src/imgui/platform/imgui_impl_glfw.cpp.obj" \
"CMakeFiles/main.dir/src/imgui/platform/imgui_impl_opengl3.cpp.obj"

# External object files for target main
main_EXTERNAL_OBJECTS =

C:/Users/34181/Desktop/gitstudy/glLearn/main.exe: CMakeFiles/main.dir/src/camera.cpp.obj
C:/Users/34181/Desktop/gitstudy/glLearn/main.exe: CMakeFiles/main.dir/src/game.cpp.obj
C:/Users/34181/Desktop/gitstudy/glLearn/main.exe: CMakeFiles/main.dir/src/glad.c.obj
C:/Users/34181/Desktop/gitstudy/glLearn/main.exe: CMakeFiles/main.dir/src/global.cpp.obj
C:/Users/34181/Desktop/gitstudy/glLearn/main.exe: CMakeFiles/main.dir/src/main.cpp.obj
C:/Users/34181/Desktop/gitstudy/glLearn/main.exe: CMakeFiles/main.dir/src/mesh.cpp.obj
C:/Users/34181/Desktop/gitstudy/glLearn/main.exe: CMakeFiles/main.dir/src/model.cpp.obj
C:/Users/34181/Desktop/gitstudy/glLearn/main.exe: CMakeFiles/main.dir/src/shader.cpp.obj
C:/Users/34181/Desktop/gitstudy/glLearn/main.exe: CMakeFiles/main.dir/src/sound.cpp.obj
C:/Users/34181/Desktop/gitstudy/glLearn/main.exe: CMakeFiles/main.dir/src/stb_image.cpp.obj
C:/Users/34181/Desktop/gitstudy/glLearn/main.exe: CMakeFiles/main.dir/src/imgui/imgui.cpp.obj
C:/Users/34181/Desktop/gitstudy/glLearn/main.exe: CMakeFiles/main.dir/src/imgui/imgui_demo.cpp.obj
C:/Users/34181/Desktop/gitstudy/glLearn/main.exe: CMakeFiles/main.dir/src/imgui/imgui_draw.cpp.obj
C:/Users/34181/Desktop/gitstudy/glLearn/main.exe: CMakeFiles/main.dir/src/imgui/imgui_tables.cpp.obj
C:/Users/34181/Desktop/gitstudy/glLearn/main.exe: CMakeFiles/main.dir/src/imgui/imgui_widgets.cpp.obj
C:/Users/34181/Desktop/gitstudy/glLearn/main.exe: CMakeFiles/main.dir/src/imgui/platform/imgui_impl_glfw.cpp.obj
C:/Users/34181/Desktop/gitstudy/glLearn/main.exe: CMakeFiles/main.dir/src/imgui/platform/imgui_impl_opengl3.cpp.obj
C:/Users/34181/Desktop/gitstudy/glLearn/main.exe: CMakeFiles/main.dir/build.make
C:/Users/34181/Desktop/gitstudy/glLearn/main.exe: C:/Users/34181/Desktop/gitstudy/glLearn/fmodL.dll
C:/Users/34181/Desktop/gitstudy/glLearn/main.exe: C:/Users/34181/Desktop/gitstudy/glLearn/lib/libglfw3.a
C:/Users/34181/Desktop/gitstudy/glLearn/main.exe: C:/Users/34181/Desktop/gitstudy/glLearn/lib/libassimp.dll.a
C:/Users/34181/Desktop/gitstudy/glLearn/main.exe: C:/Users/34181/Desktop/gitstudy/glLearn/lib/x64_mingw_posix_seh_msvcrt/libfreetype.a
C:/Users/34181/Desktop/gitstudy/glLearn/main.exe: CMakeFiles/main.dir/linkLibs.rsp
C:/Users/34181/Desktop/gitstudy/glLearn/main.exe: CMakeFiles/main.dir/objects1.rsp
C:/Users/34181/Desktop/gitstudy/glLearn/main.exe: CMakeFiles/main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:\Users\34181\Desktop\gitstudy\glLearn\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_18) "Linking CXX executable C:\Users\34181\Desktop\gitstudy\glLearn\main.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\main.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/main.dir/build: C:/Users/34181/Desktop/gitstudy/glLearn/main.exe
.PHONY : CMakeFiles/main.dir/build

CMakeFiles/main.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\main.dir\cmake_clean.cmake
.PHONY : CMakeFiles/main.dir/clean

CMakeFiles/main.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\34181\Desktop\gitstudy\glLearn C:\Users\34181\Desktop\gitstudy\glLearn C:\Users\34181\Desktop\gitstudy\glLearn\build C:\Users\34181\Desktop\gitstudy\glLearn\build C:\Users\34181\Desktop\gitstudy\glLearn\build\CMakeFiles\main.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/main.dir/depend

