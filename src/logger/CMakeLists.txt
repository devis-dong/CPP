cmake_minimum_required(VERSION 3.0.0)
# name of the project
project(prj VERSION 0.1.0)

# source code file
set(src dslogger.cpp)
# name of output lib
set(lib dslogger)

# add included path for building
include_directories(${PROJECT_BINARY_DIR}/../../inc ${PROJECT_BINARY_DIR}/../../src)
# add linked path for building
link_directories(${PROJECT_BINARY_DIR}/../../bin)
# generate the dll
add_library(${lib} SHARED ${src})
# link the dependent lib
target_link_libraries(${lib} "libdswatch.dll")
# where to store the lib
set(LIBRARY_OUTPUT_PATH  ${PROJECT_BINARY_DIR}/lib)
# where to install the lib
set(CMAKE_INSTALL_PREFIX ${PROJECT_BINARY_DIR}/../../)
# install lib
install(
    TARGETS  ${lib}
    # LIBRARY dynamic link library
    LIBRARY 
)

# .h files to install
# set(headfiles dslogger.h)
# install .h files
# install(FILES ${headfiles} DESTINATION ${PROJECT_BINARY_DIR}/../../inc)
