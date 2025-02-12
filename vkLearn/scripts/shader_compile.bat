@echo off
if "%1"=="" (
    echo 请输入要编译的GLSL着色器源文件路径
    exit /b 1
)
set input_path=%~dp1
set file_name=%~n1
cd Bin
glslc.exe "%1" -o "%input_path%%file_name%.spv"