# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /var/lib/snapd/snap/clion/103/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /var/lib/snapd/snap/clion/103/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ivan/technopark/C++

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ivan/technopark/C++/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/C__.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/C__.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/C__.dir/flags.make

CMakeFiles/C__.dir/main.c.o: CMakeFiles/C__.dir/flags.make
CMakeFiles/C__.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ivan/technopark/C++/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/C__.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/C__.dir/main.c.o   -c /home/ivan/technopark/C++/main.c

CMakeFiles/C__.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/C__.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/ivan/technopark/C++/main.c > CMakeFiles/C__.dir/main.c.i

CMakeFiles/C__.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/C__.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/ivan/technopark/C++/main.c -o CMakeFiles/C__.dir/main.c.s

# Object files for target C__
C___OBJECTS = \
"CMakeFiles/C__.dir/main.c.o"

# External object files for target C__
C___EXTERNAL_OBJECTS =

C__: CMakeFiles/C__.dir/main.c.o
C__: CMakeFiles/C__.dir/build.make
C__: CMakeFiles/C__.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ivan/technopark/C++/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable C__"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/C__.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/C__.dir/build: C__

.PHONY : CMakeFiles/C__.dir/build

CMakeFiles/C__.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/C__.dir/cmake_clean.cmake
.PHONY : CMakeFiles/C__.dir/clean

CMakeFiles/C__.dir/depend:
	cd /home/ivan/technopark/C++/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ivan/technopark/C++ /home/ivan/technopark/C++ /home/ivan/technopark/C++/cmake-build-debug /home/ivan/technopark/C++/cmake-build-debug /home/ivan/technopark/C++/cmake-build-debug/CMakeFiles/C__.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/C__.dir/depend

