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
CMAKE_SOURCE_DIR = E:\Coding\C++\test\logger

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = E:\Coding\C++\build\test

# Include any dependencies generated for this target.
include CMakeFiles/main.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/main.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/main.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/main.dir/flags.make

CMakeFiles/main.dir/dslogger_test.cpp.obj: CMakeFiles/main.dir/flags.make
CMakeFiles/main.dir/dslogger_test.cpp.obj: CMakeFiles/main.dir/includes_CXX.rsp
CMakeFiles/main.dir/dslogger_test.cpp.obj: E:/Coding/C++/test/logger/dslogger_test.cpp
CMakeFiles/main.dir/dslogger_test.cpp.obj: CMakeFiles/main.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=E:\Coding\C++\build\test\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/main.dir/dslogger_test.cpp.obj"
	D:\ProgramFiles\mingw\x86_64-8.1.0-posix-seh-rt_v6-rev0\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/main.dir/dslogger_test.cpp.obj -MF CMakeFiles\main.dir\dslogger_test.cpp.obj.d -o CMakeFiles\main.dir\dslogger_test.cpp.obj -c E:\Coding\C++\test\logger\dslogger_test.cpp

CMakeFiles/main.dir/dslogger_test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/main.dir/dslogger_test.cpp.i"
	D:\ProgramFiles\mingw\x86_64-8.1.0-posix-seh-rt_v6-rev0\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E E:\Coding\C++\test\logger\dslogger_test.cpp > CMakeFiles\main.dir\dslogger_test.cpp.i

CMakeFiles/main.dir/dslogger_test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/main.dir/dslogger_test.cpp.s"
	D:\ProgramFiles\mingw\x86_64-8.1.0-posix-seh-rt_v6-rev0\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S E:\Coding\C++\test\logger\dslogger_test.cpp -o CMakeFiles\main.dir\dslogger_test.cpp.s

# Object files for target main
main_OBJECTS = \
"CMakeFiles/main.dir/dslogger_test.cpp.obj"

# External object files for target main
main_EXTERNAL_OBJECTS =

E:/Coding/C++/bin/main.exe: CMakeFiles/main.dir/dslogger_test.cpp.obj
E:/Coding/C++/bin/main.exe: CMakeFiles/main.dir/build.make
E:/Coding/C++/bin/main.exe: CMakeFiles/main.dir/linklibs.rsp
E:/Coding/C++/bin/main.exe: CMakeFiles/main.dir/objects1.rsp
E:/Coding/C++/bin/main.exe: CMakeFiles/main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=E:\Coding\C++\build\test\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable E:\Coding\C++\bin\main.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\main.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/main.dir/build: E:/Coding/C++/bin/main.exe
.PHONY : CMakeFiles/main.dir/build

CMakeFiles/main.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\main.dir\cmake_clean.cmake
.PHONY : CMakeFiles/main.dir/clean

CMakeFiles/main.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" E:\Coding\C++\test\logger E:\Coding\C++\test\logger E:\Coding\C++\build\test E:\Coding\C++\build\test E:\Coding\C++\build\test\CMakeFiles\main.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/main.dir/depend

