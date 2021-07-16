cmake_minimum_required(VERSION 3.20)
project(test_dslogger VERSION 1.0)
set(src test_dslogger.cpp)
set(exe test_dslogger)

include_directories("E:/Coding/C++/build/logger/install/inc")
link_directories("E:/Coding/C++/build/logger/install/bin")
set(EXECUTABLE_OUTPUT_PATH "E:/Coding/C++/build/logger/install/bin")

add_executable(${exe} ${src})
target_link_libraries(${exe} "libdslogger.dll")


