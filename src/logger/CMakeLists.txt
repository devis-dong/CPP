cmake_minimum_required(VERSION 3.0.0)
# name of the project
project(prj VERSION 0.1.0)

# source code file
set(src dslogger.cpp)
# name of output lib
set(lib dslogger)
# where to store the lib
set(lib_path  ${PROJECT_BINARY_DIR}/lib)
# where to install the lib
set(install_path  "../../")
# .h files to install
set(headfiles dslogger.h)


# add included path for building
include_directories("../../inc" "../../src")
# generate the dll
add_library(${lib} SHARED ${src})
# set path to store the lib
set(LIBRARY_OUTPUT_PATH  ${lib_path})
# set path to install the lib
set(CMAKE_INSTALL_PREFIX ${install_path})
# install lib
install(
    TARGETS  ${lib}
    # LIBRARY dynamic link library
    LIBRARY
)

# path to install .h files
# set(inc_path ${install_path}/inc)
# install .h files
# install(FILES ${headfiles} DESTINATION ${inc_path})
