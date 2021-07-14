cmake_minimum_required(VERSION 3.20)
project(logger_test VERSION 1.0)
set(src dslogger_test.cpp)
set(exe dslogger_test)

include_directories("../../inc" "../../src")
link_directories("../../bin")
set(EXECUTABLE_OUTPUT_PATH "../../bin")

add_executable(${exe} ${src})
target_link_libraries(${exe} "libdslogger.dll")


