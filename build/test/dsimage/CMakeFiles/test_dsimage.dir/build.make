# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.21

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = D:\ProgramFiles\cmake\bin\cmake.exe

# The command to remove a file.
RM = D:\ProgramFiles\cmake\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = E:\Coding\C++\test\dsimage

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = E:\Coding\C++\build\test\dsimage

# Include any dependencies generated for this target.
include CMakeFiles/test_dsimage.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/test_dsimage.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/test_dsimage.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test_dsimage.dir/flags.make

CMakeFiles/test_dsimage.dir/test_dsimage.cpp.obj: CMakeFiles/test_dsimage.dir/flags.make
CMakeFiles/test_dsimage.dir/test_dsimage.cpp.obj: CMakeFiles/test_dsimage.dir/includes_CXX.rsp
CMakeFiles/test_dsimage.dir/test_dsimage.cpp.obj: E:/Coding/C++/test/dsimage/test_dsimage.cpp
CMakeFiles/test_dsimage.dir/test_dsimage.cpp.obj: CMakeFiles/test_dsimage.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\Coding\C++\build\test\dsimage\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/test_dsimage.dir/test_dsimage.cpp.obj"
	D:\ProgramFiles\mingw\x86_64-8.1.0-posix-seh-rt_v6-rev0\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test_dsimage.dir/test_dsimage.cpp.obj -MF CMakeFiles\test_dsimage.dir\test_dsimage.cpp.obj.d -o CMakeFiles\test_dsimage.dir\test_dsimage.cpp.obj -c E:\Coding\C++\test\dsimage\test_dsimage.cpp

CMakeFiles/test_dsimage.dir/test_dsimage.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_dsimage.dir/test_dsimage.cpp.i"
	D:\ProgramFiles\mingw\x86_64-8.1.0-posix-seh-rt_v6-rev0\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\Coding\C++\test\dsimage\test_dsimage.cpp > CMakeFiles\test_dsimage.dir\test_dsimage.cpp.i

CMakeFiles/test_dsimage.dir/test_dsimage.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_dsimage.dir/test_dsimage.cpp.s"
	D:\ProgramFiles\mingw\x86_64-8.1.0-posix-seh-rt_v6-rev0\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S E:\Coding\C++\test\dsimage\test_dsimage.cpp -o CMakeFiles\test_dsimage.dir\test_dsimage.cpp.s

# Object files for target test_dsimage
test_dsimage_OBJECTS = \
"CMakeFiles/test_dsimage.dir/test_dsimage.cpp.obj"

# External object files for target test_dsimage
test_dsimage_EXTERNAL_OBJECTS =

E:/Coding/C++/build/dsimage/install/bin/test_dsimage.exe: CMakeFiles/test_dsimage.dir/test_dsimage.cpp.obj
E:/Coding/C++/build/dsimage/install/bin/test_dsimage.exe: CMakeFiles/test_dsimage.dir/build.make
E:/Coding/C++/build/dsimage/install/bin/test_dsimage.exe: CMakeFiles/test_dsimage.dir/linklibs.rsp
E:/Coding/C++/build/dsimage/install/bin/test_dsimage.exe: CMakeFiles/test_dsimage.dir/objects1.rsp
E:/Coding/C++/build/dsimage/install/bin/test_dsimage.exe: CMakeFiles/test_dsimage.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=E:\Coding\C++\build\test\dsimage\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable E:\Coding\C++\build\dsimage\install\bin\test_dsimage.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\test_dsimage.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test_dsimage.dir/build: E:/Coding/C++/build/dsimage/install/bin/test_dsimage.exe
.PHONY : CMakeFiles/test_dsimage.dir/build

CMakeFiles/test_dsimage.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\test_dsimage.dir\cmake_clean.cmake
.PHONY : CMakeFiles/test_dsimage.dir/clean

CMakeFiles/test_dsimage.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" E:\Coding\C++\test\dsimage E:\Coding\C++\test\dsimage E:\Coding\C++\build\test\dsimage E:\Coding\C++\build\test\dsimage E:\Coding\C++\build\test\dsimage\CMakeFiles\test_dsimage.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test_dsimage.dir/depend
