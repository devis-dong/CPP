cmake_minimum_required(VERSION 3.0.0)
# name of the project
project(prj VERSION 0.1.0)

# source code file
set(src dsimage.cpp)
# name of output lib
set(lib dsimage)

# add included path for building
include_directories("E:/Coding/C++/src/common" "E:/Coding/C++/build/dslogger/install/inc" "E:/Coding/C++/build/dsmat/install/inc")
# add linked path for building
link_directories("E:/Coding/C++/build/dslogger/install/bin" "E:/Coding/C++/build/dsmat/install/bin")
# generate the dll
add_library(${lib} SHARED ${src})
# link the dependent lib
target_link_libraries(${lib} "libdslogger.dll" "libdsmat.dll")
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
install(FILES "dsimage.h" "../common/dsdefine.h" "../dsmat/dsmat.h" DESTINATION ${PROJECT_BINARY_DIR}/install/inc)
install(FILES "E:/Coding/C++/build/dslogger/install/bin/libdslogger.dll" DESTINATION ${PROJECT_BINARY_DIR}/install/bin)
install(FILES "E:/Coding/C++/build/dslogger/install/lib/libdslogger.dll.a" DESTINATION ${PROJECT_BINARY_DIR}/install/lib)
install(FILES "E:/Coding/C++/build/dsmat/install/bin/libdsmat.dll" DESTINATION ${PROJECT_BINARY_DIR}/install/bin)
install(FILES "E:/Coding/C++/build/dsmat/install/lib/libdsmat.dll.a" DESTINATION ${PROJECT_BINARY_DIR}/install/lib)
