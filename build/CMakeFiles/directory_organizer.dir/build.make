# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_SOURCE_DIR = /home/talocha/C/DirectoryOrganizer

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/talocha/C/DirectoryOrganizer/build

# Include any dependencies generated for this target.
include CMakeFiles/directory_organizer.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/directory_organizer.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/directory_organizer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/directory_organizer.dir/flags.make

CMakeFiles/directory_organizer.dir/directory_organizer.c.o: CMakeFiles/directory_organizer.dir/flags.make
CMakeFiles/directory_organizer.dir/directory_organizer.c.o: /home/talocha/C/DirectoryOrganizer/directory_organizer.c
CMakeFiles/directory_organizer.dir/directory_organizer.c.o: CMakeFiles/directory_organizer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/talocha/C/DirectoryOrganizer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/directory_organizer.dir/directory_organizer.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/directory_organizer.dir/directory_organizer.c.o -MF CMakeFiles/directory_organizer.dir/directory_organizer.c.o.d -o CMakeFiles/directory_organizer.dir/directory_organizer.c.o -c /home/talocha/C/DirectoryOrganizer/directory_organizer.c

CMakeFiles/directory_organizer.dir/directory_organizer.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/directory_organizer.dir/directory_organizer.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/talocha/C/DirectoryOrganizer/directory_organizer.c > CMakeFiles/directory_organizer.dir/directory_organizer.c.i

CMakeFiles/directory_organizer.dir/directory_organizer.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/directory_organizer.dir/directory_organizer.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/talocha/C/DirectoryOrganizer/directory_organizer.c -o CMakeFiles/directory_organizer.dir/directory_organizer.c.s

# Object files for target directory_organizer
directory_organizer_OBJECTS = \
"CMakeFiles/directory_organizer.dir/directory_organizer.c.o"

# External object files for target directory_organizer
directory_organizer_EXTERNAL_OBJECTS =

directory_organizer: CMakeFiles/directory_organizer.dir/directory_organizer.c.o
directory_organizer: CMakeFiles/directory_organizer.dir/build.make
directory_organizer: CMakeFiles/directory_organizer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/talocha/C/DirectoryOrganizer/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable directory_organizer"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/directory_organizer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/directory_organizer.dir/build: directory_organizer
.PHONY : CMakeFiles/directory_organizer.dir/build

CMakeFiles/directory_organizer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/directory_organizer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/directory_organizer.dir/clean

CMakeFiles/directory_organizer.dir/depend:
	cd /home/talocha/C/DirectoryOrganizer/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/talocha/C/DirectoryOrganizer /home/talocha/C/DirectoryOrganizer /home/talocha/C/DirectoryOrganizer/build /home/talocha/C/DirectoryOrganizer/build /home/talocha/C/DirectoryOrganizer/build/CMakeFiles/directory_organizer.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/directory_organizer.dir/depend

