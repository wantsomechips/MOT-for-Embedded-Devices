# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CMake.app/Contents/bin/cmake

# The command to remove a file.
RM = /Applications/CMake.app/Contents/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/gaohao/Desktop/MOT

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/gaohao/Desktop/MOT/build

# Include any dependencies generated for this target.
include src/CMakeFiles/funcs.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/CMakeFiles/funcs.dir/compiler_depend.make

# Include the progress variables for this target.
include src/CMakeFiles/funcs.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/funcs.dir/flags.make

src/CMakeFiles/funcs.dir/funcs.cpp.o: src/CMakeFiles/funcs.dir/flags.make
src/CMakeFiles/funcs.dir/funcs.cpp.o: ../src/funcs.cpp
src/CMakeFiles/funcs.dir/funcs.cpp.o: src/CMakeFiles/funcs.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/gaohao/Desktop/MOT/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/funcs.dir/funcs.cpp.o"
	cd /Users/gaohao/Desktop/MOT/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/funcs.dir/funcs.cpp.o -MF CMakeFiles/funcs.dir/funcs.cpp.o.d -o CMakeFiles/funcs.dir/funcs.cpp.o -c /Users/gaohao/Desktop/MOT/src/funcs.cpp

src/CMakeFiles/funcs.dir/funcs.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/funcs.dir/funcs.cpp.i"
	cd /Users/gaohao/Desktop/MOT/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/gaohao/Desktop/MOT/src/funcs.cpp > CMakeFiles/funcs.dir/funcs.cpp.i

src/CMakeFiles/funcs.dir/funcs.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/funcs.dir/funcs.cpp.s"
	cd /Users/gaohao/Desktop/MOT/build/src && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/gaohao/Desktop/MOT/src/funcs.cpp -o CMakeFiles/funcs.dir/funcs.cpp.s

# Object files for target funcs
funcs_OBJECTS = \
"CMakeFiles/funcs.dir/funcs.cpp.o"

# External object files for target funcs
funcs_EXTERNAL_OBJECTS =

../bin/libfuncs.a: src/CMakeFiles/funcs.dir/funcs.cpp.o
../bin/libfuncs.a: src/CMakeFiles/funcs.dir/build.make
../bin/libfuncs.a: src/CMakeFiles/funcs.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/gaohao/Desktop/MOT/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library ../../bin/libfuncs.a"
	cd /Users/gaohao/Desktop/MOT/build/src && $(CMAKE_COMMAND) -P CMakeFiles/funcs.dir/cmake_clean_target.cmake
	cd /Users/gaohao/Desktop/MOT/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/funcs.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/funcs.dir/build: ../bin/libfuncs.a
.PHONY : src/CMakeFiles/funcs.dir/build

src/CMakeFiles/funcs.dir/clean:
	cd /Users/gaohao/Desktop/MOT/build/src && $(CMAKE_COMMAND) -P CMakeFiles/funcs.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/funcs.dir/clean

src/CMakeFiles/funcs.dir/depend:
	cd /Users/gaohao/Desktop/MOT/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/gaohao/Desktop/MOT /Users/gaohao/Desktop/MOT/src /Users/gaohao/Desktop/MOT/build /Users/gaohao/Desktop/MOT/build/src /Users/gaohao/Desktop/MOT/build/src/CMakeFiles/funcs.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/funcs.dir/depend

