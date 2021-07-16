cmake_minimum_required(VERSION 3.0.0)
# name of the project
project(prj VERSION 0.1.0)

# source code file
set(src dslogger.cpp)
# name of output lib
set(lib dslogger)

# add included path for building
include_directories("E:/Coding/C++/src/common")
# generate the dll
add_library(${lib} SHARED ${src})
# where to store the lib
set(LIBRARY_OUTPUT_PATH  ${PROJECT_BINARY_DIR}/lib)
# where to install the lib
set(CMAKE_INSTALL_PREFIX ${PROJECT_BINARY_DIR}/install)
# install lib
install(
    TARGETS  ${lib}
    # LIBRARY dynamic link library
    LIBRARY 
)
# install .h files
install(FILES "dslogger.h" "../common/dsdefine.h" DESTINATION ${PROJECT_BINARY_DIR}/install/inc)
