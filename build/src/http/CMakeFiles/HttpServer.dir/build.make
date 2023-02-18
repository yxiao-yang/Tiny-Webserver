# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/podest/tiny-network

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/podest/tiny-network/build

# Include any dependencies generated for this target.
include src/http/CMakeFiles/HttpServer.dir/depend.make

# Include the progress variables for this target.
include src/http/CMakeFiles/HttpServer.dir/progress.make

# Include the compile flags for this target's objects.
include src/http/CMakeFiles/HttpServer.dir/flags.make

src/http/CMakeFiles/HttpServer.dir/HttpServer.cc.o: src/http/CMakeFiles/HttpServer.dir/flags.make
src/http/CMakeFiles/HttpServer.dir/HttpServer.cc.o: ../src/http/HttpServer.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/podest/tiny-network/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/http/CMakeFiles/HttpServer.dir/HttpServer.cc.o"
	cd /home/podest/tiny-network/build/src/http && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/HttpServer.dir/HttpServer.cc.o -c /home/podest/tiny-network/src/http/HttpServer.cc

src/http/CMakeFiles/HttpServer.dir/HttpServer.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/HttpServer.dir/HttpServer.cc.i"
	cd /home/podest/tiny-network/build/src/http && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/podest/tiny-network/src/http/HttpServer.cc > CMakeFiles/HttpServer.dir/HttpServer.cc.i

src/http/CMakeFiles/HttpServer.dir/HttpServer.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/HttpServer.dir/HttpServer.cc.s"
	cd /home/podest/tiny-network/build/src/http && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/podest/tiny-network/src/http/HttpServer.cc -o CMakeFiles/HttpServer.dir/HttpServer.cc.s

src/http/CMakeFiles/HttpServer.dir/HttpServer.cc.o.requires:

.PHONY : src/http/CMakeFiles/HttpServer.dir/HttpServer.cc.o.requires

src/http/CMakeFiles/HttpServer.dir/HttpServer.cc.o.provides: src/http/CMakeFiles/HttpServer.dir/HttpServer.cc.o.requires
	$(MAKE) -f src/http/CMakeFiles/HttpServer.dir/build.make src/http/CMakeFiles/HttpServer.dir/HttpServer.cc.o.provides.build
.PHONY : src/http/CMakeFiles/HttpServer.dir/HttpServer.cc.o.provides

src/http/CMakeFiles/HttpServer.dir/HttpServer.cc.o.provides.build: src/http/CMakeFiles/HttpServer.dir/HttpServer.cc.o


src/http/CMakeFiles/HttpServer.dir/HttpResponse.cc.o: src/http/CMakeFiles/HttpServer.dir/flags.make
src/http/CMakeFiles/HttpServer.dir/HttpResponse.cc.o: ../src/http/HttpResponse.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/podest/tiny-network/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/http/CMakeFiles/HttpServer.dir/HttpResponse.cc.o"
	cd /home/podest/tiny-network/build/src/http && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/HttpServer.dir/HttpResponse.cc.o -c /home/podest/tiny-network/src/http/HttpResponse.cc

src/http/CMakeFiles/HttpServer.dir/HttpResponse.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/HttpServer.dir/HttpResponse.cc.i"
	cd /home/podest/tiny-network/build/src/http && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/podest/tiny-network/src/http/HttpResponse.cc > CMakeFiles/HttpServer.dir/HttpResponse.cc.i

src/http/CMakeFiles/HttpServer.dir/HttpResponse.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/HttpServer.dir/HttpResponse.cc.s"
	cd /home/podest/tiny-network/build/src/http && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/podest/tiny-network/src/http/HttpResponse.cc -o CMakeFiles/HttpServer.dir/HttpResponse.cc.s

src/http/CMakeFiles/HttpServer.dir/HttpResponse.cc.o.requires:

.PHONY : src/http/CMakeFiles/HttpServer.dir/HttpResponse.cc.o.requires

src/http/CMakeFiles/HttpServer.dir/HttpResponse.cc.o.provides: src/http/CMakeFiles/HttpServer.dir/HttpResponse.cc.o.requires
	$(MAKE) -f src/http/CMakeFiles/HttpServer.dir/build.make src/http/CMakeFiles/HttpServer.dir/HttpResponse.cc.o.provides.build
.PHONY : src/http/CMakeFiles/HttpServer.dir/HttpResponse.cc.o.provides

src/http/CMakeFiles/HttpServer.dir/HttpResponse.cc.o.provides.build: src/http/CMakeFiles/HttpServer.dir/HttpResponse.cc.o


src/http/CMakeFiles/HttpServer.dir/HttpContext.cc.o: src/http/CMakeFiles/HttpServer.dir/flags.make
src/http/CMakeFiles/HttpServer.dir/HttpContext.cc.o: ../src/http/HttpContext.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/podest/tiny-network/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/http/CMakeFiles/HttpServer.dir/HttpContext.cc.o"
	cd /home/podest/tiny-network/build/src/http && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/HttpServer.dir/HttpContext.cc.o -c /home/podest/tiny-network/src/http/HttpContext.cc

src/http/CMakeFiles/HttpServer.dir/HttpContext.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/HttpServer.dir/HttpContext.cc.i"
	cd /home/podest/tiny-network/build/src/http && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/podest/tiny-network/src/http/HttpContext.cc > CMakeFiles/HttpServer.dir/HttpContext.cc.i

src/http/CMakeFiles/HttpServer.dir/HttpContext.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/HttpServer.dir/HttpContext.cc.s"
	cd /home/podest/tiny-network/build/src/http && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/podest/tiny-network/src/http/HttpContext.cc -o CMakeFiles/HttpServer.dir/HttpContext.cc.s

src/http/CMakeFiles/HttpServer.dir/HttpContext.cc.o.requires:

.PHONY : src/http/CMakeFiles/HttpServer.dir/HttpContext.cc.o.requires

src/http/CMakeFiles/HttpServer.dir/HttpContext.cc.o.provides: src/http/CMakeFiles/HttpServer.dir/HttpContext.cc.o.requires
	$(MAKE) -f src/http/CMakeFiles/HttpServer.dir/build.make src/http/CMakeFiles/HttpServer.dir/HttpContext.cc.o.provides.build
.PHONY : src/http/CMakeFiles/HttpServer.dir/HttpContext.cc.o.provides

src/http/CMakeFiles/HttpServer.dir/HttpContext.cc.o.provides.build: src/http/CMakeFiles/HttpServer.dir/HttpContext.cc.o


src/http/CMakeFiles/HttpServer.dir/main.cc.o: src/http/CMakeFiles/HttpServer.dir/flags.make
src/http/CMakeFiles/HttpServer.dir/main.cc.o: ../src/http/main.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/podest/tiny-network/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object src/http/CMakeFiles/HttpServer.dir/main.cc.o"
	cd /home/podest/tiny-network/build/src/http && /usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/HttpServer.dir/main.cc.o -c /home/podest/tiny-network/src/http/main.cc

src/http/CMakeFiles/HttpServer.dir/main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/HttpServer.dir/main.cc.i"
	cd /home/podest/tiny-network/build/src/http && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/podest/tiny-network/src/http/main.cc > CMakeFiles/HttpServer.dir/main.cc.i

src/http/CMakeFiles/HttpServer.dir/main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/HttpServer.dir/main.cc.s"
	cd /home/podest/tiny-network/build/src/http && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/podest/tiny-network/src/http/main.cc -o CMakeFiles/HttpServer.dir/main.cc.s

src/http/CMakeFiles/HttpServer.dir/main.cc.o.requires:

.PHONY : src/http/CMakeFiles/HttpServer.dir/main.cc.o.requires

src/http/CMakeFiles/HttpServer.dir/main.cc.o.provides: src/http/CMakeFiles/HttpServer.dir/main.cc.o.requires
	$(MAKE) -f src/http/CMakeFiles/HttpServer.dir/build.make src/http/CMakeFiles/HttpServer.dir/main.cc.o.provides.build
.PHONY : src/http/CMakeFiles/HttpServer.dir/main.cc.o.provides

src/http/CMakeFiles/HttpServer.dir/main.cc.o.provides.build: src/http/CMakeFiles/HttpServer.dir/main.cc.o


# Object files for target HttpServer
HttpServer_OBJECTS = \
"CMakeFiles/HttpServer.dir/HttpServer.cc.o" \
"CMakeFiles/HttpServer.dir/HttpResponse.cc.o" \
"CMakeFiles/HttpServer.dir/HttpContext.cc.o" \
"CMakeFiles/HttpServer.dir/main.cc.o"

# External object files for target HttpServer
HttpServer_EXTERNAL_OBJECTS =

../src/http/HttpServer: src/http/CMakeFiles/HttpServer.dir/HttpServer.cc.o
../src/http/HttpServer: src/http/CMakeFiles/HttpServer.dir/HttpResponse.cc.o
../src/http/HttpServer: src/http/CMakeFiles/HttpServer.dir/HttpContext.cc.o
../src/http/HttpServer: src/http/CMakeFiles/HttpServer.dir/main.cc.o
../src/http/HttpServer: src/http/CMakeFiles/HttpServer.dir/build.make
../src/http/HttpServer: ../lib/libtiny_network.so
../src/http/HttpServer: src/http/CMakeFiles/HttpServer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/podest/tiny-network/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable ../../../src/http/HttpServer"
	cd /home/podest/tiny-network/build/src/http && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/HttpServer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/http/CMakeFiles/HttpServer.dir/build: ../src/http/HttpServer

.PHONY : src/http/CMakeFiles/HttpServer.dir/build

src/http/CMakeFiles/HttpServer.dir/requires: src/http/CMakeFiles/HttpServer.dir/HttpServer.cc.o.requires
src/http/CMakeFiles/HttpServer.dir/requires: src/http/CMakeFiles/HttpServer.dir/HttpResponse.cc.o.requires
src/http/CMakeFiles/HttpServer.dir/requires: src/http/CMakeFiles/HttpServer.dir/HttpContext.cc.o.requires
src/http/CMakeFiles/HttpServer.dir/requires: src/http/CMakeFiles/HttpServer.dir/main.cc.o.requires

.PHONY : src/http/CMakeFiles/HttpServer.dir/requires

src/http/CMakeFiles/HttpServer.dir/clean:
	cd /home/podest/tiny-network/build/src/http && $(CMAKE_COMMAND) -P CMakeFiles/HttpServer.dir/cmake_clean.cmake
.PHONY : src/http/CMakeFiles/HttpServer.dir/clean

src/http/CMakeFiles/HttpServer.dir/depend:
	cd /home/podest/tiny-network/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/podest/tiny-network /home/podest/tiny-network/src/http /home/podest/tiny-network/build /home/podest/tiny-network/build/src/http /home/podest/tiny-network/build/src/http/CMakeFiles/HttpServer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/http/CMakeFiles/HttpServer.dir/depend

