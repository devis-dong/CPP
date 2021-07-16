cmake_minimum_required(VERSION 3.20)
project(test_dsimage VERSION 1.0)
set(src test_dsimage.cpp)
set(exe test_dsimage)

include_directories("E:/Coding/C++/build/dsimage/install/inc")
link_directories("E:/Coding/C++/build/dsimage/install/bin")
set(EXECUTABLE_OUTPUT_PATH "E:/Coding/C++/build/dsimage/install/bin")

add_executable(${exe} ${src})
target_link_libraries(${exe} "libdsimage.dll" "libdsmat.dll")
