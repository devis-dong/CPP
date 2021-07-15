cmake_minimum_required(VERSION 3.20)
project(test_dslogger VERSION 1.0)
set(src test_dslogger.cpp)
set(exe test_dslogger)

include_directories(${PROJECT_BINARY_DIR}/../../../src ${PROJECT_BINARY_DIR}../../../src)
link_directories(${PROJECT_BINARY_DIR}/../../../bin)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/../../../bin)

add_executable(${exe} ${src})
target_link_libraries(${exe} "libdslogger.dll")


