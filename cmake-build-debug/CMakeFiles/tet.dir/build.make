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
include CMakeFiles/tet.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/tet.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/tet.dir/flags.make

CMakeFiles/tet.dir/src/Scanner.cpp.o: CMakeFiles/tet.dir/flags.make
CMakeFiles/tet.dir/src/Scanner.cpp.o: ../src/Scanner.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/wangruoxuan/ClionProjects/complier/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/tet.dir/src/Scanner.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/tet.dir/src/Scanner.cpp.o -c /Users/wangruoxuan/ClionProjects/complier/src/Scanner.cpp

CMakeFiles/tet.dir/src/Scanner.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/tet.dir/src/Scanner.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/wangruoxuan/ClionProjects/complier/src/Scanner.cpp > CMakeFiles/tet.dir/src/Scanner.cpp.i

CMakeFiles/tet.dir/src/Scanner.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/tet.dir/src/Scanner.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/wangruoxuan/ClionProjects/complier/src/Scanner.cpp -o CMakeFiles/tet.dir/src/Scanner.cpp.s

CMakeFiles/tet.dir/src/Scanner.cpp.o.requires:

.PHONY : CMakeFiles/tet.dir/src/Scanner.cpp.o.requires

CMakeFiles/tet.dir/src/Scanner.cpp.o.provides: CMakeFiles/tet.dir/src/Scanner.cpp.o.requires
	$(MAKE) -f CMakeFiles/tet.dir/build.make CMakeFiles/tet.dir/src/Scanner.cpp.o.provides.build
.PHONY : CMakeFiles/tet.dir/src/Scanner.cpp.o.provides

CMakeFiles/tet.dir/src/Scanner.cpp.o.provides.build: CMakeFiles/tet.dir/src/Scanner.cpp.o


# Object files for target tet
tet_OBJECTS = \
"CMakeFiles/tet.dir/src/Scanner.cpp.o"

# External object files for target tet
tet_EXTERNAL_OBJECTS =

tet: CMakeFiles/tet.dir/src/Scanner.cpp.o
tet: CMakeFiles/tet.dir/build.make
tet: CMakeFiles/tet.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/wangruoxuan/ClionProjects/complier/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable tet"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/tet.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/tet.dir/build: tet

.PHONY : CMakeFiles/tet.dir/build

CMakeFiles/tet.dir/requires: CMakeFiles/tet.dir/src/Scanner.cpp.o.requires

.PHONY : CMakeFiles/tet.dir/requires

CMakeFiles/tet.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/tet.dir/cmake_clean.cmake
.PHONY : CMakeFiles/tet.dir/clean

CMakeFiles/tet.dir/depend:
	cd /Users/wangruoxuan/ClionProjects/complier/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/wangruoxuan/ClionProjects/complier /Users/wangruoxuan/ClionProjects/complier /Users/wangruoxuan/ClionProjects/complier/cmake-build-debug /Users/wangruoxuan/ClionProjects/complier/cmake-build-debug /Users/wangruoxuan/ClionProjects/complier/cmake-build-debug/CMakeFiles/tet.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/tet.dir/depend

