cmake_minimum_required(VERSION 3.5)

project(subprojects)

# Add sub directories
# 定义子目录src，用以递归的调用src中的MakeLists.txt
add_subdirectory(public)
add_subdirectory(app)
add_subdirectory(src)
