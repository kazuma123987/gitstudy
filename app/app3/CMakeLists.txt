# Set the project name
project (app3)
# Add a library with the above sources
add_library(${PROJECT_NAME} app3.c)
add_library(lib::app3 ALIAS ${PROJECT_NAME})

target_include_directories( ${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}  ${subprojects_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} ${subprojects_SOURCE_DIR}/lib/libstatic_library.a)
