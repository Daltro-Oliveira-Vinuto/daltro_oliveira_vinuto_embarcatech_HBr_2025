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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/daltro/Codes/embedded/rp/build/_deps/picotool-src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/daltro/Codes/embedded/rp/build/_deps/picotool-build

# Include any dependencies generated for this target.
include elf/CMakeFiles/elf.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include elf/CMakeFiles/elf.dir/compiler_depend.make

# Include the compile flags for this target's objects.
include elf/CMakeFiles/elf.dir/flags.make

elf/CMakeFiles/elf.dir/elf_file.cpp.o: elf/CMakeFiles/elf.dir/flags.make
elf/CMakeFiles/elf.dir/elf_file.cpp.o: /home/daltro/Codes/embedded/rp/build/_deps/picotool-src/elf/elf_file.cpp
elf/CMakeFiles/elf.dir/elf_file.cpp.o: elf/CMakeFiles/elf.dir/compiler_depend.ts
	cd /home/daltro/Codes/embedded/rp/build/_deps/picotool-build/elf && /bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT elf/CMakeFiles/elf.dir/elf_file.cpp.o -MF CMakeFiles/elf.dir/elf_file.cpp.o.d -o CMakeFiles/elf.dir/elf_file.cpp.o -c /home/daltro/Codes/embedded/rp/build/_deps/picotool-src/elf/elf_file.cpp

elf/CMakeFiles/elf.dir/elf_file.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/elf.dir/elf_file.cpp.i"
	cd /home/daltro/Codes/embedded/rp/build/_deps/picotool-build/elf && /bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/daltro/Codes/embedded/rp/build/_deps/picotool-src/elf/elf_file.cpp > CMakeFiles/elf.dir/elf_file.cpp.i

elf/CMakeFiles/elf.dir/elf_file.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/elf.dir/elf_file.cpp.s"
	cd /home/daltro/Codes/embedded/rp/build/_deps/picotool-build/elf && /bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/daltro/Codes/embedded/rp/build/_deps/picotool-src/elf/elf_file.cpp -o CMakeFiles/elf.dir/elf_file.cpp.s

# Object files for target elf
elf_OBJECTS = \
"CMakeFiles/elf.dir/elf_file.cpp.o"

# External object files for target elf
elf_EXTERNAL_OBJECTS =

elf/libelf.a: elf/CMakeFiles/elf.dir/elf_file.cpp.o
elf/libelf.a: elf/CMakeFiles/elf.dir/build.make
elf/libelf.a: elf/CMakeFiles/elf.dir/link.txt
	cd /home/daltro/Codes/embedded/rp/build/_deps/picotool-build/elf && $(CMAKE_COMMAND) -P CMakeFiles/elf.dir/cmake_clean_target.cmake
	cd /home/daltro/Codes/embedded/rp/build/_deps/picotool-build/elf && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/elf.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
elf/CMakeFiles/elf.dir/build: elf/libelf.a
.PHONY : elf/CMakeFiles/elf.dir/build

elf/CMakeFiles/elf.dir/clean:
	cd /home/daltro/Codes/embedded/rp/build/_deps/picotool-build/elf && $(CMAKE_COMMAND) -P CMakeFiles/elf.dir/cmake_clean.cmake
.PHONY : elf/CMakeFiles/elf.dir/clean

elf/CMakeFiles/elf.dir/depend:
	cd /home/daltro/Codes/embedded/rp/build/_deps/picotool-build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/daltro/Codes/embedded/rp/build/_deps/picotool-src /home/daltro/Codes/embedded/rp/build/_deps/picotool-src/elf /home/daltro/Codes/embedded/rp/build/_deps/picotool-build /home/daltro/Codes/embedded/rp/build/_deps/picotool-build/elf /home/daltro/Codes/embedded/rp/build/_deps/picotool-build/elf/CMakeFiles/elf.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : elf/CMakeFiles/elf.dir/depend

