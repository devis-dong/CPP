cmake_minimum_required(VERSION 3.20)
project(test_dswatch VERSION 1.0)
set(src test_dswatch.cpp)
set(exe test_dswatch)

# add included path for building
include_directories(${PROJECT_BINARY_DIR}/../../../src ${PROJECT_BINARY_DIR}../../../src)
# add linked path for building
link_directories(${PROJECT_BINARY_DIR}/../../../bin)
# set output path
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../../../bin)
# generate the exe
add_executable(${exe} ${src})
# link the dependent lib
target_link_libraries(${exe} "libdswatch.dll")



