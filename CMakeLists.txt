cmake_minimum_required(VERSION 3.5)

project(static_library)

############################################################
# Create a library
############################################################

#Generate the static library from the library sources
add_library(static_library STATIC 
    src/Static.c
)

target_include_directories(static_library
    PUBLIC 
        ${PROJECT_SOURCE_DIR}/include
)


############################################################
# Create an executable
############################################################

# Add an executable with the above sources
add_executable(hello_binary 
    src/main.c
)

# link the new static_library target with the hello_binary target
target_link_libraries( hello_binary
    PRIVATE 
        static_library
)

