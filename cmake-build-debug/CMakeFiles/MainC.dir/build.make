# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.8

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
CMAKE_SOURCE_DIR = /Users/enterprising/CLionProjects/MainC

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/enterprising/CLionProjects/MainC/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/MainC.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/MainC.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/MainC.dir/flags.make

CMakeFiles/MainC.dir/echoServerMain.c.o: CMakeFiles/MainC.dir/flags.make
CMakeFiles/MainC.dir/echoServerMain.c.o: ../echoServerMain.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/enterprising/CLionProjects/MainC/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/MainC.dir/echoServerMain.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/MainC.dir/echoServerMain.c.o   -c /Users/enterprising/CLionProjects/MainC/echoServerMain.c

CMakeFiles/MainC.dir/echoServerMain.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/MainC.dir/echoServerMain.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/enterprising/CLionProjects/MainC/echoServerMain.c > CMakeFiles/MainC.dir/echoServerMain.c.i

CMakeFiles/MainC.dir/echoServerMain.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/MainC.dir/echoServerMain.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/enterprising/CLionProjects/MainC/echoServerMain.c -o CMakeFiles/MainC.dir/echoServerMain.c.s

CMakeFiles/MainC.dir/echoServerMain.c.o.requires:

.PHONY : CMakeFiles/MainC.dir/echoServerMain.c.o.requires

CMakeFiles/MainC.dir/echoServerMain.c.o.provides: CMakeFiles/MainC.dir/echoServerMain.c.o.requires
	$(MAKE) -f CMakeFiles/MainC.dir/build.make CMakeFiles/MainC.dir/echoServerMain.c.o.provides.build
.PHONY : CMakeFiles/MainC.dir/echoServerMain.c.o.provides

CMakeFiles/MainC.dir/echoServerMain.c.o.provides.build: CMakeFiles/MainC.dir/echoServerMain.c.o


# Object files for target MainC
MainC_OBJECTS = \
"CMakeFiles/MainC.dir/echoServerMain.c.o"

# External object files for target MainC
MainC_EXTERNAL_OBJECTS =

MainC: CMakeFiles/MainC.dir/echoServerMain.c.o
MainC: CMakeFiles/MainC.dir/build.make
MainC: CMakeFiles/MainC.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/enterprising/CLionProjects/MainC/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable MainC"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/MainC.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/MainC.dir/build: MainC

.PHONY : CMakeFiles/MainC.dir/build

CMakeFiles/MainC.dir/requires: CMakeFiles/MainC.dir/echoServerMain.c.o.requires

.PHONY : CMakeFiles/MainC.dir/requires

CMakeFiles/MainC.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/MainC.dir/cmake_clean.cmake
.PHONY : CMakeFiles/MainC.dir/clean

CMakeFiles/MainC.dir/depend:
	cd /Users/enterprising/CLionProjects/MainC/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/enterprising/CLionProjects/MainC /Users/enterprising/CLionProjects/MainC /Users/enterprising/CLionProjects/MainC/cmake-build-debug /Users/enterprising/CLionProjects/MainC/cmake-build-debug /Users/enterprising/CLionProjects/MainC/cmake-build-debug/CMakeFiles/MainC.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/MainC.dir/depend

