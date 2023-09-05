project(main)

# Create the executable
add_executable(${PROJECT_NAME} main.c)

target_include_directories( ${PROJECT_NAME}
    PUBLIC ${subprojects_SOURCE_DIR}/include
)
#link_directories( ${subprojects_SOURCE_DIR}/lib )

# Link the static library from subproject1 using it's alias sub::lib1
# Link the header only library from subproject2 using it's alias sub::lib2
# This will cause the include directories for that target to be added to this project
target_link_libraries(${PROJECT_NAME}
    lib::app1
    lib::app2
    lib::app3
    lib::public1
    lib::public2
    ${subprojects_SOURCE_DIR}/lib/libstatic_library.a
)
