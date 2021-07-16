cmake_minimum_required(VERSION 3.20)
project(test_opencv VERSION 1.0)
set(src test_opencv.cpp)
set(exe test_opencv)

include_directories("E:/Coding/C++/build/opencv/install/inc")
link_directories("E:/Coding/C++/build/opencv/install/bin")
set(EXECUTABLE_OUTPUT_PATH "E:/Coding/C++/build/opencv/install/bin")

add_executable(${exe} ${src})
target_link_libraries(${exe} "libopencv_highgui3413.dll" "libopencv_imgcodecs3413.dll" "libopencv_imgproc3413.dll" "libopencv_core3413.dll")
