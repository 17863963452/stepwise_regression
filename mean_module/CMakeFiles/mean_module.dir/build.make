# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.18

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/liushimin/statistics/c_test/unit3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/liushimin/statistics/c_test/unit3

# Include any dependencies generated for this target.
include mean_module/CMakeFiles/mean_module.dir/depend.make

# Include the progress variables for this target.
include mean_module/CMakeFiles/mean_module.dir/progress.make

# Include the compile flags for this target's objects.
include mean_module/CMakeFiles/mean_module.dir/flags.make

mean_module/CMakeFiles/mean_module.dir/mean_module.c.o: mean_module/CMakeFiles/mean_module.dir/flags.make
mean_module/CMakeFiles/mean_module.dir/mean_module.c.o: mean_module/mean_module.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/liushimin/statistics/c_test/unit3/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object mean_module/CMakeFiles/mean_module.dir/mean_module.c.o"
	cd /home/liushimin/statistics/c_test/unit3/mean_module && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/mean_module.dir/mean_module.c.o -c /home/liushimin/statistics/c_test/unit3/mean_module/mean_module.c

mean_module/CMakeFiles/mean_module.dir/mean_module.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/mean_module.dir/mean_module.c.i"
	cd /home/liushimin/statistics/c_test/unit3/mean_module && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/liushimin/statistics/c_test/unit3/mean_module/mean_module.c > CMakeFiles/mean_module.dir/mean_module.c.i

mean_module/CMakeFiles/mean_module.dir/mean_module.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/mean_module.dir/mean_module.c.s"
	cd /home/liushimin/statistics/c_test/unit3/mean_module && /usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/liushimin/statistics/c_test/unit3/mean_module/mean_module.c -o CMakeFiles/mean_module.dir/mean_module.c.s

# Object files for target mean_module
mean_module_OBJECTS = \
"CMakeFiles/mean_module.dir/mean_module.c.o"

# External object files for target mean_module
mean_module_EXTERNAL_OBJECTS =

mean_module/libmean_module.a: mean_module/CMakeFiles/mean_module.dir/mean_module.c.o
mean_module/libmean_module.a: mean_module/CMakeFiles/mean_module.dir/build.make
mean_module/libmean_module.a: mean_module/CMakeFiles/mean_module.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/liushimin/statistics/c_test/unit3/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libmean_module.a"
	cd /home/liushimin/statistics/c_test/unit3/mean_module && $(CMAKE_COMMAND) -P CMakeFiles/mean_module.dir/cmake_clean_target.cmake
	cd /home/liushimin/statistics/c_test/unit3/mean_module && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mean_module.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
mean_module/CMakeFiles/mean_module.dir/build: mean_module/libmean_module.a

.PHONY : mean_module/CMakeFiles/mean_module.dir/build

mean_module/CMakeFiles/mean_module.dir/clean:
	cd /home/liushimin/statistics/c_test/unit3/mean_module && $(CMAKE_COMMAND) -P CMakeFiles/mean_module.dir/cmake_clean.cmake
.PHONY : mean_module/CMakeFiles/mean_module.dir/clean

mean_module/CMakeFiles/mean_module.dir/depend:
	cd /home/liushimin/statistics/c_test/unit3 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/liushimin/statistics/c_test/unit3 /home/liushimin/statistics/c_test/unit3/mean_module /home/liushimin/statistics/c_test/unit3 /home/liushimin/statistics/c_test/unit3/mean_module /home/liushimin/statistics/c_test/unit3/mean_module/CMakeFiles/mean_module.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : mean_module/CMakeFiles/mean_module.dir/depend

