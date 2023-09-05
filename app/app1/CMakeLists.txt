# Set the project name
project (app1)
# Add a library with the above sources
add_library(${PROJECT_NAME} app1.c)
add_library(lib::app1 ALIAS ${PROJECT_NAME})

target_include_directories( ${PROJECT_NAME}
    PUBLIC ${PROJECT_SOURCE_DIR}
)
