cmake_minimum_required(VERSION 3.20)
project(test_dsmat VERSION 1.0)
set(src test_dsmat.cpp)
set(exe test_dsmat)

include_directories("E:/Coding/C++/build/mat/install/inc")
link_directories("E:/Coding/C++/build/mat/install/bin")
set(EXECUTABLE_OUTPUT_PATH "E:/Coding/C++/build/mat/install/bin")

add_executable(${exe} ${src})
target_link_libraries(${exe} "libdsmat.dll")
