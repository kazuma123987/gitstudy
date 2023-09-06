project(main)

# 添加exe文件
add_executable(${PROJECT_NAME} main.c)

#设定目标target=$(PROJECT_NAME),即main,可理解target_include_directories用法为：
#target_include_directories( target [PRIVATE|INTERFACE|PUBLIC] dir1 dir2 ...)，
#目标target由add_executable(target dir1 dir2)或add_library(target <SHARED|STATIC|MODULE|OBJECT|UNKNOWN> IMPORTED [GLOBAL])决定，
#实际上是要生成的exe文件或lib/dll/a/so文件的名字<name>
target_include_directories( ${PROJECT_NAME}
    PRIVATE ${subprojects_SOURCE_DIR}/include
)
#连接子目录的库文件：

# 从subprojects（子目录）连接target（目标）所依赖的alias库（别名库）以及由Static.c所生成的静态库libstatic_library.a
# 这将会添加生成.exe文件所需要的头文件
target_link_libraries(${PROJECT_NAME}
    lib::app1
    lib::app2
    lib::app3
    lib::public1
    lib::public2
    ${subprojects_SOURCE_DIR}/lib/libstatic_library.a
)
