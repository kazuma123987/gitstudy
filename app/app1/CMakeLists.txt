# 设置PROJECT_NAME(项目名)
project (app1)

# 生成一个与PROJECT_NAME(项目名)同名的库并将app1.c添加到其中
add_library(${PROJECT_NAME} app1.c)

#为与PROJECT_NAME(项目名)同名的库起一个别名lib::app1
add_library(lib::app1 ALIAS ${PROJECT_NAME})

#指定target（目标）所依赖的头文件地址，且将访问权限设置为PUBLIC，即app1.c和app1.h都可以使用该地址的库
#其中PROJECT_SOURCE_DIR为当前项目所在地址（即当前CMakeLists.txt所在地址）
target_include_directories( ${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})
