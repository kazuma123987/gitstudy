project(code-demo);
aux_source_directory(src SRC_SUB);
add_executable(demo ${SRC_SUB});
include_directories(include);