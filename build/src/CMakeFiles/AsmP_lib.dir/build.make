# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

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
CMAKE_SOURCE_DIR = /home/dmytro/Desktop/bp/AsmPTest

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/dmytro/Desktop/bp/AsmPTest/build

# Include any dependencies generated for this target.
include src/CMakeFiles/AsmP_lib.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/CMakeFiles/AsmP_lib.dir/compiler_depend.make

# Include the progress variables for this target.
include src/CMakeFiles/AsmP_lib.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/AsmP_lib.dir/flags.make

src/CMakeFiles/AsmP_lib.dir/DataVectors.cpp.o: src/CMakeFiles/AsmP_lib.dir/flags.make
src/CMakeFiles/AsmP_lib.dir/DataVectors.cpp.o: /home/dmytro/Desktop/bp/AsmPTest/src/DataVectors.cpp
src/CMakeFiles/AsmP_lib.dir/DataVectors.cpp.o: src/CMakeFiles/AsmP_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dmytro/Desktop/bp/AsmPTest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/CMakeFiles/AsmP_lib.dir/DataVectors.cpp.o"
	cd /home/dmytro/Desktop/bp/AsmPTest/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/AsmP_lib.dir/DataVectors.cpp.o -MF CMakeFiles/AsmP_lib.dir/DataVectors.cpp.o.d -o CMakeFiles/AsmP_lib.dir/DataVectors.cpp.o -c /home/dmytro/Desktop/bp/AsmPTest/src/DataVectors.cpp

src/CMakeFiles/AsmP_lib.dir/DataVectors.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AsmP_lib.dir/DataVectors.cpp.i"
	cd /home/dmytro/Desktop/bp/AsmPTest/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dmytro/Desktop/bp/AsmPTest/src/DataVectors.cpp > CMakeFiles/AsmP_lib.dir/DataVectors.cpp.i

src/CMakeFiles/AsmP_lib.dir/DataVectors.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AsmP_lib.dir/DataVectors.cpp.s"
	cd /home/dmytro/Desktop/bp/AsmPTest/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dmytro/Desktop/bp/AsmPTest/src/DataVectors.cpp -o CMakeFiles/AsmP_lib.dir/DataVectors.cpp.s

src/CMakeFiles/AsmP_lib.dir/SpectrumLoader.cpp.o: src/CMakeFiles/AsmP_lib.dir/flags.make
src/CMakeFiles/AsmP_lib.dir/SpectrumLoader.cpp.o: /home/dmytro/Desktop/bp/AsmPTest/src/SpectrumLoader.cpp
src/CMakeFiles/AsmP_lib.dir/SpectrumLoader.cpp.o: src/CMakeFiles/AsmP_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dmytro/Desktop/bp/AsmPTest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/AsmP_lib.dir/SpectrumLoader.cpp.o"
	cd /home/dmytro/Desktop/bp/AsmPTest/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/AsmP_lib.dir/SpectrumLoader.cpp.o -MF CMakeFiles/AsmP_lib.dir/SpectrumLoader.cpp.o.d -o CMakeFiles/AsmP_lib.dir/SpectrumLoader.cpp.o -c /home/dmytro/Desktop/bp/AsmPTest/src/SpectrumLoader.cpp

src/CMakeFiles/AsmP_lib.dir/SpectrumLoader.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AsmP_lib.dir/SpectrumLoader.cpp.i"
	cd /home/dmytro/Desktop/bp/AsmPTest/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dmytro/Desktop/bp/AsmPTest/src/SpectrumLoader.cpp > CMakeFiles/AsmP_lib.dir/SpectrumLoader.cpp.i

src/CMakeFiles/AsmP_lib.dir/SpectrumLoader.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AsmP_lib.dir/SpectrumLoader.cpp.s"
	cd /home/dmytro/Desktop/bp/AsmPTest/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dmytro/Desktop/bp/AsmPTest/src/SpectrumLoader.cpp -o CMakeFiles/AsmP_lib.dir/SpectrumLoader.cpp.s

src/CMakeFiles/AsmP_lib.dir/ThroughputFunc.cpp.o: src/CMakeFiles/AsmP_lib.dir/flags.make
src/CMakeFiles/AsmP_lib.dir/ThroughputFunc.cpp.o: /home/dmytro/Desktop/bp/AsmPTest/src/ThroughputFunc.cpp
src/CMakeFiles/AsmP_lib.dir/ThroughputFunc.cpp.o: src/CMakeFiles/AsmP_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dmytro/Desktop/bp/AsmPTest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/CMakeFiles/AsmP_lib.dir/ThroughputFunc.cpp.o"
	cd /home/dmytro/Desktop/bp/AsmPTest/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/AsmP_lib.dir/ThroughputFunc.cpp.o -MF CMakeFiles/AsmP_lib.dir/ThroughputFunc.cpp.o.d -o CMakeFiles/AsmP_lib.dir/ThroughputFunc.cpp.o -c /home/dmytro/Desktop/bp/AsmPTest/src/ThroughputFunc.cpp

src/CMakeFiles/AsmP_lib.dir/ThroughputFunc.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AsmP_lib.dir/ThroughputFunc.cpp.i"
	cd /home/dmytro/Desktop/bp/AsmPTest/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dmytro/Desktop/bp/AsmPTest/src/ThroughputFunc.cpp > CMakeFiles/AsmP_lib.dir/ThroughputFunc.cpp.i

src/CMakeFiles/AsmP_lib.dir/ThroughputFunc.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AsmP_lib.dir/ThroughputFunc.cpp.s"
	cd /home/dmytro/Desktop/bp/AsmPTest/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dmytro/Desktop/bp/AsmPTest/src/ThroughputFunc.cpp -o CMakeFiles/AsmP_lib.dir/ThroughputFunc.cpp.s

src/CMakeFiles/AsmP_lib.dir/main.cpp.o: src/CMakeFiles/AsmP_lib.dir/flags.make
src/CMakeFiles/AsmP_lib.dir/main.cpp.o: /home/dmytro/Desktop/bp/AsmPTest/src/main.cpp
src/CMakeFiles/AsmP_lib.dir/main.cpp.o: src/CMakeFiles/AsmP_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dmytro/Desktop/bp/AsmPTest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object src/CMakeFiles/AsmP_lib.dir/main.cpp.o"
	cd /home/dmytro/Desktop/bp/AsmPTest/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/AsmP_lib.dir/main.cpp.o -MF CMakeFiles/AsmP_lib.dir/main.cpp.o.d -o CMakeFiles/AsmP_lib.dir/main.cpp.o -c /home/dmytro/Desktop/bp/AsmPTest/src/main.cpp

src/CMakeFiles/AsmP_lib.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AsmP_lib.dir/main.cpp.i"
	cd /home/dmytro/Desktop/bp/AsmPTest/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dmytro/Desktop/bp/AsmPTest/src/main.cpp > CMakeFiles/AsmP_lib.dir/main.cpp.i

src/CMakeFiles/AsmP_lib.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AsmP_lib.dir/main.cpp.s"
	cd /home/dmytro/Desktop/bp/AsmPTest/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dmytro/Desktop/bp/AsmPTest/src/main.cpp -o CMakeFiles/AsmP_lib.dir/main.cpp.s

src/CMakeFiles/AsmP_lib.dir/utilities.cpp.o: src/CMakeFiles/AsmP_lib.dir/flags.make
src/CMakeFiles/AsmP_lib.dir/utilities.cpp.o: /home/dmytro/Desktop/bp/AsmPTest/src/utilities.cpp
src/CMakeFiles/AsmP_lib.dir/utilities.cpp.o: src/CMakeFiles/AsmP_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dmytro/Desktop/bp/AsmPTest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object src/CMakeFiles/AsmP_lib.dir/utilities.cpp.o"
	cd /home/dmytro/Desktop/bp/AsmPTest/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/AsmP_lib.dir/utilities.cpp.o -MF CMakeFiles/AsmP_lib.dir/utilities.cpp.o.d -o CMakeFiles/AsmP_lib.dir/utilities.cpp.o -c /home/dmytro/Desktop/bp/AsmPTest/src/utilities.cpp

src/CMakeFiles/AsmP_lib.dir/utilities.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AsmP_lib.dir/utilities.cpp.i"
	cd /home/dmytro/Desktop/bp/AsmPTest/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dmytro/Desktop/bp/AsmPTest/src/utilities.cpp > CMakeFiles/AsmP_lib.dir/utilities.cpp.i

src/CMakeFiles/AsmP_lib.dir/utilities.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AsmP_lib.dir/utilities.cpp.s"
	cd /home/dmytro/Desktop/bp/AsmPTest/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dmytro/Desktop/bp/AsmPTest/src/utilities.cpp -o CMakeFiles/AsmP_lib.dir/utilities.cpp.s

# Object files for target AsmP_lib
AsmP_lib_OBJECTS = \
"CMakeFiles/AsmP_lib.dir/DataVectors.cpp.o" \
"CMakeFiles/AsmP_lib.dir/SpectrumLoader.cpp.o" \
"CMakeFiles/AsmP_lib.dir/ThroughputFunc.cpp.o" \
"CMakeFiles/AsmP_lib.dir/main.cpp.o" \
"CMakeFiles/AsmP_lib.dir/utilities.cpp.o"

# External object files for target AsmP_lib
AsmP_lib_EXTERNAL_OBJECTS =

src/libAsmP_lib.a: src/CMakeFiles/AsmP_lib.dir/DataVectors.cpp.o
src/libAsmP_lib.a: src/CMakeFiles/AsmP_lib.dir/SpectrumLoader.cpp.o
src/libAsmP_lib.a: src/CMakeFiles/AsmP_lib.dir/ThroughputFunc.cpp.o
src/libAsmP_lib.a: src/CMakeFiles/AsmP_lib.dir/main.cpp.o
src/libAsmP_lib.a: src/CMakeFiles/AsmP_lib.dir/utilities.cpp.o
src/libAsmP_lib.a: src/CMakeFiles/AsmP_lib.dir/build.make
src/libAsmP_lib.a: src/CMakeFiles/AsmP_lib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/dmytro/Desktop/bp/AsmPTest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX static library libAsmP_lib.a"
	cd /home/dmytro/Desktop/bp/AsmPTest/build/src && $(CMAKE_COMMAND) -P CMakeFiles/AsmP_lib.dir/cmake_clean_target.cmake
	cd /home/dmytro/Desktop/bp/AsmPTest/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/AsmP_lib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/AsmP_lib.dir/build: src/libAsmP_lib.a
.PHONY : src/CMakeFiles/AsmP_lib.dir/build

src/CMakeFiles/AsmP_lib.dir/clean:
	cd /home/dmytro/Desktop/bp/AsmPTest/build/src && $(CMAKE_COMMAND) -P CMakeFiles/AsmP_lib.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/AsmP_lib.dir/clean

src/CMakeFiles/AsmP_lib.dir/depend:
	cd /home/dmytro/Desktop/bp/AsmPTest/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dmytro/Desktop/bp/AsmPTest /home/dmytro/Desktop/bp/AsmPTest/src /home/dmytro/Desktop/bp/AsmPTest/build /home/dmytro/Desktop/bp/AsmPTest/build/src /home/dmytro/Desktop/bp/AsmPTest/build/src/CMakeFiles/AsmP_lib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/AsmP_lib.dir/depend

