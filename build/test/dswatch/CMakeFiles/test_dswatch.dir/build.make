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
CMAKE_SOURCE_DIR = E:\Coding\C++\test\dswatch

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = E:\Coding\C++\build\test\dswatch

# Include any dependencies generated for this target.
include CMakeFiles/test_dswatch.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/test_dswatch.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/test_dswatch.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test_dswatch.dir/flags.make

CMakeFiles/test_dswatch.dir/test_dswatch.cpp.obj: CMakeFiles/test_dswatch.dir/flags.make
CMakeFiles/test_dswatch.dir/test_dswatch.cpp.obj: CMakeFiles/test_dswatch.dir/includes_CXX.rsp
CMakeFiles/test_dswatch.dir/test_dswatch.cpp.obj: E:/Coding/C++/test/dswatch/test_dswatch.cpp
CMakeFiles/test_dswatch.dir/test_dswatch.cpp.obj: CMakeFiles/test_dswatch.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\Coding\C++\build\test\dswatch\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/test_dswatch.dir/test_dswatch.cpp.obj"
	D:\ProgramFiles\mingw\x86_64-8.1.0-posix-seh-rt_v6-rev0\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test_dswatch.dir/test_dswatch.cpp.obj -MF CMakeFiles\test_dswatch.dir\test_dswatch.cpp.obj.d -o CMakeFiles\test_dswatch.dir\test_dswatch.cpp.obj -c E:\Coding\C++\test\dswatch\test_dswatch.cpp

CMakeFiles/test_dswatch.dir/test_dswatch.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_dswatch.dir/test_dswatch.cpp.i"
	D:\ProgramFiles\mingw\x86_64-8.1.0-posix-seh-rt_v6-rev0\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\Coding\C++\test\dswatch\test_dswatch.cpp > CMakeFiles\test_dswatch.dir\test_dswatch.cpp.i

CMakeFiles/test_dswatch.dir/test_dswatch.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_dswatch.dir/test_dswatch.cpp.s"
	D:\ProgramFiles\mingw\x86_64-8.1.0-posix-seh-rt_v6-rev0\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S E:\Coding\C++\test\dswatch\test_dswatch.cpp -o CMakeFiles\test_dswatch.dir\test_dswatch.cpp.s

# Object files for target test_dswatch
test_dswatch_OBJECTS = \
"CMakeFiles/test_dswatch.dir/test_dswatch.cpp.obj"

# External object files for target test_dswatch
test_dswatch_EXTERNAL_OBJECTS =

E:/Coding/C++/build/dswatch/install/bin/test_dswatch.exe: CMakeFiles/test_dswatch.dir/test_dswatch.cpp.obj
E:/Coding/C++/build/dswatch/install/bin/test_dswatch.exe: CMakeFiles/test_dswatch.dir/build.make
E:/Coding/C++/build/dswatch/install/bin/test_dswatch.exe: CMakeFiles/test_dswatch.dir/linklibs.rsp
E:/Coding/C++/build/dswatch/install/bin/test_dswatch.exe: CMakeFiles/test_dswatch.dir/objects1.rsp
E:/Coding/C++/build/dswatch/install/bin/test_dswatch.exe: CMakeFiles/test_dswatch.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=E:\Coding\C++\build\test\dswatch\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable E:\Coding\C++\build\dswatch\install\bin\test_dswatch.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\test_dswatch.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test_dswatch.dir/build: E:/Coding/C++/build/dswatch/install/bin/test_dswatch.exe
.PHONY : CMakeFiles/test_dswatch.dir/build

CMakeFiles/test_dswatch.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\test_dswatch.dir\cmake_clean.cmake
.PHONY : CMakeFiles/test_dswatch.dir/clean

CMakeFiles/test_dswatch.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" E:\Coding\C++\test\dswatch E:\Coding\C++\test\dswatch E:\Coding\C++\build\test\dswatch E:\Coding\C++\build\test\dswatch E:\Coding\C++\build\test\dswatch\CMakeFiles\test_dswatch.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test_dswatch.dir/depend
