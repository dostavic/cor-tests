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
include src/InfilGenerator/CMakeFiles/InfilGenerator_lib.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/InfilGenerator/CMakeFiles/InfilGenerator_lib.dir/compiler_depend.make

# Include the progress variables for this target.
include src/InfilGenerator/CMakeFiles/InfilGenerator_lib.dir/progress.make

# Include the compile flags for this target's objects.
include src/InfilGenerator/CMakeFiles/InfilGenerator_lib.dir/flags.make

src/InfilGenerator/CMakeFiles/InfilGenerator_lib.dir/OutfilData.cpp.o: src/InfilGenerator/CMakeFiles/InfilGenerator_lib.dir/flags.make
src/InfilGenerator/CMakeFiles/InfilGenerator_lib.dir/OutfilData.cpp.o: /home/dmytro/Desktop/bp/AsmPTest/src/InfilGenerator/OutfilData.cpp
src/InfilGenerator/CMakeFiles/InfilGenerator_lib.dir/OutfilData.cpp.o: src/InfilGenerator/CMakeFiles/InfilGenerator_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dmytro/Desktop/bp/AsmPTest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/InfilGenerator/CMakeFiles/InfilGenerator_lib.dir/OutfilData.cpp.o"
	cd /home/dmytro/Desktop/bp/AsmPTest/build/src/InfilGenerator && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/InfilGenerator/CMakeFiles/InfilGenerator_lib.dir/OutfilData.cpp.o -MF CMakeFiles/InfilGenerator_lib.dir/OutfilData.cpp.o.d -o CMakeFiles/InfilGenerator_lib.dir/OutfilData.cpp.o -c /home/dmytro/Desktop/bp/AsmPTest/src/InfilGenerator/OutfilData.cpp

src/InfilGenerator/CMakeFiles/InfilGenerator_lib.dir/OutfilData.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/InfilGenerator_lib.dir/OutfilData.cpp.i"
	cd /home/dmytro/Desktop/bp/AsmPTest/build/src/InfilGenerator && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dmytro/Desktop/bp/AsmPTest/src/InfilGenerator/OutfilData.cpp > CMakeFiles/InfilGenerator_lib.dir/OutfilData.cpp.i

src/InfilGenerator/CMakeFiles/InfilGenerator_lib.dir/OutfilData.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/InfilGenerator_lib.dir/OutfilData.cpp.s"
	cd /home/dmytro/Desktop/bp/AsmPTest/build/src/InfilGenerator && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dmytro/Desktop/bp/AsmPTest/src/InfilGenerator/OutfilData.cpp -o CMakeFiles/InfilGenerator_lib.dir/OutfilData.cpp.s

src/InfilGenerator/CMakeFiles/InfilGenerator_lib.dir/Timestamp.cpp.o: src/InfilGenerator/CMakeFiles/InfilGenerator_lib.dir/flags.make
src/InfilGenerator/CMakeFiles/InfilGenerator_lib.dir/Timestamp.cpp.o: /home/dmytro/Desktop/bp/AsmPTest/src/InfilGenerator/Timestamp.cpp
src/InfilGenerator/CMakeFiles/InfilGenerator_lib.dir/Timestamp.cpp.o: src/InfilGenerator/CMakeFiles/InfilGenerator_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dmytro/Desktop/bp/AsmPTest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/InfilGenerator/CMakeFiles/InfilGenerator_lib.dir/Timestamp.cpp.o"
	cd /home/dmytro/Desktop/bp/AsmPTest/build/src/InfilGenerator && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/InfilGenerator/CMakeFiles/InfilGenerator_lib.dir/Timestamp.cpp.o -MF CMakeFiles/InfilGenerator_lib.dir/Timestamp.cpp.o.d -o CMakeFiles/InfilGenerator_lib.dir/Timestamp.cpp.o -c /home/dmytro/Desktop/bp/AsmPTest/src/InfilGenerator/Timestamp.cpp

src/InfilGenerator/CMakeFiles/InfilGenerator_lib.dir/Timestamp.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/InfilGenerator_lib.dir/Timestamp.cpp.i"
	cd /home/dmytro/Desktop/bp/AsmPTest/build/src/InfilGenerator && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dmytro/Desktop/bp/AsmPTest/src/InfilGenerator/Timestamp.cpp > CMakeFiles/InfilGenerator_lib.dir/Timestamp.cpp.i

src/InfilGenerator/CMakeFiles/InfilGenerator_lib.dir/Timestamp.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/InfilGenerator_lib.dir/Timestamp.cpp.s"
	cd /home/dmytro/Desktop/bp/AsmPTest/build/src/InfilGenerator && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dmytro/Desktop/bp/AsmPTest/src/InfilGenerator/Timestamp.cpp -o CMakeFiles/InfilGenerator_lib.dir/Timestamp.cpp.s

src/InfilGenerator/CMakeFiles/InfilGenerator_lib.dir/geo_to_mag.cpp.o: src/InfilGenerator/CMakeFiles/InfilGenerator_lib.dir/flags.make
src/InfilGenerator/CMakeFiles/InfilGenerator_lib.dir/geo_to_mag.cpp.o: /home/dmytro/Desktop/bp/AsmPTest/src/InfilGenerator/geo_to_mag.cpp
src/InfilGenerator/CMakeFiles/InfilGenerator_lib.dir/geo_to_mag.cpp.o: src/InfilGenerator/CMakeFiles/InfilGenerator_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dmytro/Desktop/bp/AsmPTest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/InfilGenerator/CMakeFiles/InfilGenerator_lib.dir/geo_to_mag.cpp.o"
	cd /home/dmytro/Desktop/bp/AsmPTest/build/src/InfilGenerator && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/InfilGenerator/CMakeFiles/InfilGenerator_lib.dir/geo_to_mag.cpp.o -MF CMakeFiles/InfilGenerator_lib.dir/geo_to_mag.cpp.o.d -o CMakeFiles/InfilGenerator_lib.dir/geo_to_mag.cpp.o -c /home/dmytro/Desktop/bp/AsmPTest/src/InfilGenerator/geo_to_mag.cpp

src/InfilGenerator/CMakeFiles/InfilGenerator_lib.dir/geo_to_mag.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/InfilGenerator_lib.dir/geo_to_mag.cpp.i"
	cd /home/dmytro/Desktop/bp/AsmPTest/build/src/InfilGenerator && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dmytro/Desktop/bp/AsmPTest/src/InfilGenerator/geo_to_mag.cpp > CMakeFiles/InfilGenerator_lib.dir/geo_to_mag.cpp.i

src/InfilGenerator/CMakeFiles/InfilGenerator_lib.dir/geo_to_mag.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/InfilGenerator_lib.dir/geo_to_mag.cpp.s"
	cd /home/dmytro/Desktop/bp/AsmPTest/build/src/InfilGenerator && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dmytro/Desktop/bp/AsmPTest/src/InfilGenerator/geo_to_mag.cpp -o CMakeFiles/InfilGenerator_lib.dir/geo_to_mag.cpp.s

src/InfilGenerator/CMakeFiles/InfilGenerator_lib.dir/infilGenerator.cpp.o: src/InfilGenerator/CMakeFiles/InfilGenerator_lib.dir/flags.make
src/InfilGenerator/CMakeFiles/InfilGenerator_lib.dir/infilGenerator.cpp.o: /home/dmytro/Desktop/bp/AsmPTest/src/InfilGenerator/infilGenerator.cpp
src/InfilGenerator/CMakeFiles/InfilGenerator_lib.dir/infilGenerator.cpp.o: src/InfilGenerator/CMakeFiles/InfilGenerator_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dmytro/Desktop/bp/AsmPTest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object src/InfilGenerator/CMakeFiles/InfilGenerator_lib.dir/infilGenerator.cpp.o"
	cd /home/dmytro/Desktop/bp/AsmPTest/build/src/InfilGenerator && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/InfilGenerator/CMakeFiles/InfilGenerator_lib.dir/infilGenerator.cpp.o -MF CMakeFiles/InfilGenerator_lib.dir/infilGenerator.cpp.o.d -o CMakeFiles/InfilGenerator_lib.dir/infilGenerator.cpp.o -c /home/dmytro/Desktop/bp/AsmPTest/src/InfilGenerator/infilGenerator.cpp

src/InfilGenerator/CMakeFiles/InfilGenerator_lib.dir/infilGenerator.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/InfilGenerator_lib.dir/infilGenerator.cpp.i"
	cd /home/dmytro/Desktop/bp/AsmPTest/build/src/InfilGenerator && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dmytro/Desktop/bp/AsmPTest/src/InfilGenerator/infilGenerator.cpp > CMakeFiles/InfilGenerator_lib.dir/infilGenerator.cpp.i

src/InfilGenerator/CMakeFiles/InfilGenerator_lib.dir/infilGenerator.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/InfilGenerator_lib.dir/infilGenerator.cpp.s"
	cd /home/dmytro/Desktop/bp/AsmPTest/build/src/InfilGenerator && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dmytro/Desktop/bp/AsmPTest/src/InfilGenerator/infilGenerator.cpp -o CMakeFiles/InfilGenerator_lib.dir/infilGenerator.cpp.s

src/InfilGenerator/CMakeFiles/InfilGenerator_lib.dir/main.cpp.o: src/InfilGenerator/CMakeFiles/InfilGenerator_lib.dir/flags.make
src/InfilGenerator/CMakeFiles/InfilGenerator_lib.dir/main.cpp.o: /home/dmytro/Desktop/bp/AsmPTest/src/InfilGenerator/main.cpp
src/InfilGenerator/CMakeFiles/InfilGenerator_lib.dir/main.cpp.o: src/InfilGenerator/CMakeFiles/InfilGenerator_lib.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/dmytro/Desktop/bp/AsmPTest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object src/InfilGenerator/CMakeFiles/InfilGenerator_lib.dir/main.cpp.o"
	cd /home/dmytro/Desktop/bp/AsmPTest/build/src/InfilGenerator && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/InfilGenerator/CMakeFiles/InfilGenerator_lib.dir/main.cpp.o -MF CMakeFiles/InfilGenerator_lib.dir/main.cpp.o.d -o CMakeFiles/InfilGenerator_lib.dir/main.cpp.o -c /home/dmytro/Desktop/bp/AsmPTest/src/InfilGenerator/main.cpp

src/InfilGenerator/CMakeFiles/InfilGenerator_lib.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/InfilGenerator_lib.dir/main.cpp.i"
	cd /home/dmytro/Desktop/bp/AsmPTest/build/src/InfilGenerator && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/dmytro/Desktop/bp/AsmPTest/src/InfilGenerator/main.cpp > CMakeFiles/InfilGenerator_lib.dir/main.cpp.i

src/InfilGenerator/CMakeFiles/InfilGenerator_lib.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/InfilGenerator_lib.dir/main.cpp.s"
	cd /home/dmytro/Desktop/bp/AsmPTest/build/src/InfilGenerator && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/dmytro/Desktop/bp/AsmPTest/src/InfilGenerator/main.cpp -o CMakeFiles/InfilGenerator_lib.dir/main.cpp.s

# Object files for target InfilGenerator_lib
InfilGenerator_lib_OBJECTS = \
"CMakeFiles/InfilGenerator_lib.dir/OutfilData.cpp.o" \
"CMakeFiles/InfilGenerator_lib.dir/Timestamp.cpp.o" \
"CMakeFiles/InfilGenerator_lib.dir/geo_to_mag.cpp.o" \
"CMakeFiles/InfilGenerator_lib.dir/infilGenerator.cpp.o" \
"CMakeFiles/InfilGenerator_lib.dir/main.cpp.o"

# External object files for target InfilGenerator_lib
InfilGenerator_lib_EXTERNAL_OBJECTS =

src/InfilGenerator/libInfilGenerator_lib.a: src/InfilGenerator/CMakeFiles/InfilGenerator_lib.dir/OutfilData.cpp.o
src/InfilGenerator/libInfilGenerator_lib.a: src/InfilGenerator/CMakeFiles/InfilGenerator_lib.dir/Timestamp.cpp.o
src/InfilGenerator/libInfilGenerator_lib.a: src/InfilGenerator/CMakeFiles/InfilGenerator_lib.dir/geo_to_mag.cpp.o
src/InfilGenerator/libInfilGenerator_lib.a: src/InfilGenerator/CMakeFiles/InfilGenerator_lib.dir/infilGenerator.cpp.o
src/InfilGenerator/libInfilGenerator_lib.a: src/InfilGenerator/CMakeFiles/InfilGenerator_lib.dir/main.cpp.o
src/InfilGenerator/libInfilGenerator_lib.a: src/InfilGenerator/CMakeFiles/InfilGenerator_lib.dir/build.make
src/InfilGenerator/libInfilGenerator_lib.a: src/InfilGenerator/CMakeFiles/InfilGenerator_lib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/dmytro/Desktop/bp/AsmPTest/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX static library libInfilGenerator_lib.a"
	cd /home/dmytro/Desktop/bp/AsmPTest/build/src/InfilGenerator && $(CMAKE_COMMAND) -P CMakeFiles/InfilGenerator_lib.dir/cmake_clean_target.cmake
	cd /home/dmytro/Desktop/bp/AsmPTest/build/src/InfilGenerator && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/InfilGenerator_lib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/InfilGenerator/CMakeFiles/InfilGenerator_lib.dir/build: src/InfilGenerator/libInfilGenerator_lib.a
.PHONY : src/InfilGenerator/CMakeFiles/InfilGenerator_lib.dir/build

src/InfilGenerator/CMakeFiles/InfilGenerator_lib.dir/clean:
	cd /home/dmytro/Desktop/bp/AsmPTest/build/src/InfilGenerator && $(CMAKE_COMMAND) -P CMakeFiles/InfilGenerator_lib.dir/cmake_clean.cmake
.PHONY : src/InfilGenerator/CMakeFiles/InfilGenerator_lib.dir/clean

src/InfilGenerator/CMakeFiles/InfilGenerator_lib.dir/depend:
	cd /home/dmytro/Desktop/bp/AsmPTest/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/dmytro/Desktop/bp/AsmPTest /home/dmytro/Desktop/bp/AsmPTest/src/InfilGenerator /home/dmytro/Desktop/bp/AsmPTest/build /home/dmytro/Desktop/bp/AsmPTest/build/src/InfilGenerator /home/dmytro/Desktop/bp/AsmPTest/build/src/InfilGenerator/CMakeFiles/InfilGenerator_lib.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/InfilGenerator/CMakeFiles/InfilGenerator_lib.dir/depend

