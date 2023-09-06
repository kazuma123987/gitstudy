# Set the project name
project (public1)

# Add a library with the above sources
add_library(${PROJECT_NAME} public1.c)
add_library(lib::public1 ALIAS ${PROJECT_NAME})

target_include_directories( ${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR})
