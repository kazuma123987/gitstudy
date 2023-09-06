# Set the project name
project (app2)
# Add a library with the above sources
add_library(${PROJECT_NAME} app2.c)
add_library(lib::app2 ALIAS ${PROJECT_NAME})

target_include_directories( ${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})

target_link_libraries(${PROJECT_NAME} lib::public2)
