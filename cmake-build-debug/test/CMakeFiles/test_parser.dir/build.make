# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.6

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/wangruoxuan/ClionProjects/complier

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/wangruoxuan/ClionProjects/complier/cmake-build-debug

# Include any dependencies generated for this target.
include test/CMakeFiles/test_parser.dir/depend.make

# Include the progress variables for this target.
include test/CMakeFiles/test_parser.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/test_parser.dir/flags.make

test/CMakeFiles/test_parser.dir/src/test_parser.cpp.o: test/CMakeFiles/test_parser.dir/flags.make
test/CMakeFiles/test_parser.dir/src/test_parser.cpp.o: ../test/src/test_parser.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/wangruoxuan/ClionProjects/complier/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/test_parser.dir/src/test_parser.cpp.o"
	cd /Users/wangruoxuan/ClionProjects/complier/cmake-build-debug/test && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_parser.dir/src/test_parser.cpp.o -c /Users/wangruoxuan/ClionProjects/complier/test/src/test_parser.cpp

test/CMakeFiles/test_parser.dir/src/test_parser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_parser.dir/src/test_parser.cpp.i"
	cd /Users/wangruoxuan/ClionProjects/complier/cmake-build-debug/test && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/wangruoxuan/ClionProjects/complier/test/src/test_parser.cpp > CMakeFiles/test_parser.dir/src/test_parser.cpp.i

test/CMakeFiles/test_parser.dir/src/test_parser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_parser.dir/src/test_parser.cpp.s"
	cd /Users/wangruoxuan/ClionProjects/complier/cmake-build-debug/test && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/wangruoxuan/ClionProjects/complier/test/src/test_parser.cpp -o CMakeFiles/test_parser.dir/src/test_parser.cpp.s

test/CMakeFiles/test_parser.dir/src/test_parser.cpp.o.requires:

.PHONY : test/CMakeFiles/test_parser.dir/src/test_parser.cpp.o.requires

test/CMakeFiles/test_parser.dir/src/test_parser.cpp.o.provides: test/CMakeFiles/test_parser.dir/src/test_parser.cpp.o.requires
	$(MAKE) -f test/CMakeFiles/test_parser.dir/build.make test/CMakeFiles/test_parser.dir/src/test_parser.cpp.o.provides.build
.PHONY : test/CMakeFiles/test_parser.dir/src/test_parser.cpp.o.provides

test/CMakeFiles/test_parser.dir/src/test_parser.cpp.o.provides.build: test/CMakeFiles/test_parser.dir/src/test_parser.cpp.o


# Object files for target test_parser
test_parser_OBJECTS = \
"CMakeFiles/test_parser.dir/src/test_parser.cpp.o"

# External object files for target test_parser
test_parser_EXTERNAL_OBJECTS =

test/test_parser: test/CMakeFiles/test_parser.dir/src/test_parser.cpp.o
test/test_parser: test/CMakeFiles/test_parser.dir/build.make
test/test_parser: libsource_lib.a
test/test_parser: test/CMakeFiles/test_parser.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/wangruoxuan/ClionProjects/complier/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test_parser"
	cd /Users/wangruoxuan/ClionProjects/complier/cmake-build-debug/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_parser.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/test_parser.dir/build: test/test_parser

.PHONY : test/CMakeFiles/test_parser.dir/build

test/CMakeFiles/test_parser.dir/requires: test/CMakeFiles/test_parser.dir/src/test_parser.cpp.o.requires

.PHONY : test/CMakeFiles/test_parser.dir/requires

test/CMakeFiles/test_parser.dir/clean:
	cd /Users/wangruoxuan/ClionProjects/complier/cmake-build-debug/test && $(CMAKE_COMMAND) -P CMakeFiles/test_parser.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/test_parser.dir/clean

test/CMakeFiles/test_parser.dir/depend:
	cd /Users/wangruoxuan/ClionProjects/complier/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/wangruoxuan/ClionProjects/complier /Users/wangruoxuan/ClionProjects/complier/test /Users/wangruoxuan/ClionProjects/complier/cmake-build-debug /Users/wangruoxuan/ClionProjects/complier/cmake-build-debug/test /Users/wangruoxuan/ClionProjects/complier/cmake-build-debug/test/CMakeFiles/test_parser.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/test_parser.dir/depend

