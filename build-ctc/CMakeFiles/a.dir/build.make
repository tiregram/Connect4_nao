# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.9

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
CMAKE_SOURCE_DIR = /home/ruhtra/nao/naoqi-sdk/doc/dev/cpp/examples/core/Connect4_nao

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ruhtra/nao/naoqi-sdk/doc/dev/cpp/examples/core/Connect4_nao/build-ctc

# Include any dependencies generated for this target.
include CMakeFiles/a.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/a.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/a.dir/flags.make

CMakeFiles/a.dir/src/Main.cpp.o: CMakeFiles/a.dir/flags.make
CMakeFiles/a.dir/src/Main.cpp.o: ../src/Main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ruhtra/nao/naoqi-sdk/doc/dev/cpp/examples/core/Connect4_nao/build-ctc/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/a.dir/src/Main.cpp.o"
	/home/ruhtra/nao/ctc/cross/bin/i686-aldebaran-linux-gnu-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/a.dir/src/Main.cpp.o -c /home/ruhtra/nao/naoqi-sdk/doc/dev/cpp/examples/core/Connect4_nao/src/Main.cpp

CMakeFiles/a.dir/src/Main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/a.dir/src/Main.cpp.i"
	/home/ruhtra/nao/ctc/cross/bin/i686-aldebaran-linux-gnu-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ruhtra/nao/naoqi-sdk/doc/dev/cpp/examples/core/Connect4_nao/src/Main.cpp > CMakeFiles/a.dir/src/Main.cpp.i

CMakeFiles/a.dir/src/Main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/a.dir/src/Main.cpp.s"
	/home/ruhtra/nao/ctc/cross/bin/i686-aldebaran-linux-gnu-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ruhtra/nao/naoqi-sdk/doc/dev/cpp/examples/core/Connect4_nao/src/Main.cpp -o CMakeFiles/a.dir/src/Main.cpp.s

CMakeFiles/a.dir/src/Main.cpp.o.requires:

.PHONY : CMakeFiles/a.dir/src/Main.cpp.o.requires

CMakeFiles/a.dir/src/Main.cpp.o.provides: CMakeFiles/a.dir/src/Main.cpp.o.requires
	$(MAKE) -f CMakeFiles/a.dir/build.make CMakeFiles/a.dir/src/Main.cpp.o.provides.build
.PHONY : CMakeFiles/a.dir/src/Main.cpp.o.provides

CMakeFiles/a.dir/src/Main.cpp.o.provides.build: CMakeFiles/a.dir/src/Main.cpp.o


CMakeFiles/a.dir/src/Reactions.cpp.o: CMakeFiles/a.dir/flags.make
CMakeFiles/a.dir/src/Reactions.cpp.o: ../src/Reactions.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ruhtra/nao/naoqi-sdk/doc/dev/cpp/examples/core/Connect4_nao/build-ctc/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/a.dir/src/Reactions.cpp.o"
	/home/ruhtra/nao/ctc/cross/bin/i686-aldebaran-linux-gnu-g++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/a.dir/src/Reactions.cpp.o -c /home/ruhtra/nao/naoqi-sdk/doc/dev/cpp/examples/core/Connect4_nao/src/Reactions.cpp

CMakeFiles/a.dir/src/Reactions.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/a.dir/src/Reactions.cpp.i"
	/home/ruhtra/nao/ctc/cross/bin/i686-aldebaran-linux-gnu-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ruhtra/nao/naoqi-sdk/doc/dev/cpp/examples/core/Connect4_nao/src/Reactions.cpp > CMakeFiles/a.dir/src/Reactions.cpp.i

CMakeFiles/a.dir/src/Reactions.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/a.dir/src/Reactions.cpp.s"
	/home/ruhtra/nao/ctc/cross/bin/i686-aldebaran-linux-gnu-g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ruhtra/nao/naoqi-sdk/doc/dev/cpp/examples/core/Connect4_nao/src/Reactions.cpp -o CMakeFiles/a.dir/src/Reactions.cpp.s

CMakeFiles/a.dir/src/Reactions.cpp.o.requires:

.PHONY : CMakeFiles/a.dir/src/Reactions.cpp.o.requires

CMakeFiles/a.dir/src/Reactions.cpp.o.provides: CMakeFiles/a.dir/src/Reactions.cpp.o.requires
	$(MAKE) -f CMakeFiles/a.dir/build.make CMakeFiles/a.dir/src/Reactions.cpp.o.provides.build
.PHONY : CMakeFiles/a.dir/src/Reactions.cpp.o.provides

CMakeFiles/a.dir/src/Reactions.cpp.o.provides.build: CMakeFiles/a.dir/src/Reactions.cpp.o


# Object files for target a
a_OBJECTS = \
"CMakeFiles/a.dir/src/Main.cpp.o" \
"CMakeFiles/a.dir/src/Reactions.cpp.o"

# External object files for target a
a_EXTERNAL_OBJECTS =

sdk/bin/a: CMakeFiles/a.dir/src/Main.cpp.o
sdk/bin/a: CMakeFiles/a.dir/src/Reactions.cpp.o
sdk/bin/a: CMakeFiles/a.dir/build.make
sdk/bin/a: /home/ruhtra/nao/ctc/libnaoqi/lib/libalproxies.so
sdk/bin/a: /home/ruhtra/nao/ctc/libnaoqi/lib/libalcommon.so
sdk/bin/a: /home/ruhtra/nao/ctc/boost/lib/libboost_signals-mt-1_55.so
sdk/bin/a: /home/ruhtra/nao/ctc/libnaoqi/lib/librttools.so
sdk/bin/a: /home/ruhtra/nao/ctc/libnaoqi/lib/libalvalue.so
sdk/bin/a: /home/ruhtra/nao/ctc/libnaoqi/lib/libalerror.so
sdk/bin/a: /home/ruhtra/nao/ctc/libnaoqi/lib/libqimessaging.so
sdk/bin/a: /home/ruhtra/nao/ctc/libnaoqi/lib/libqitype.so
sdk/bin/a: /home/ruhtra/nao/ctc/libnaoqi/lib/libqi.so
sdk/bin/a: /home/ruhtra/nao/ctc/boost/lib/libboost_chrono-mt-1_55.so
sdk/bin/a: /home/ruhtra/nao/ctc/boost/lib/libboost_filesystem-mt-1_55.so
sdk/bin/a: /home/ruhtra/nao/ctc/boost/lib/libboost_program_options-mt-1_55.so
sdk/bin/a: /home/ruhtra/nao/ctc/boost/lib/libboost_regex-mt-1_55.so
sdk/bin/a: /home/ruhtra/nao/ctc/cross/i686-aldebaran-linux-gnu/sysroot/usr/lib/libdl.so
sdk/bin/a: /home/ruhtra/nao/ctc/cross/i686-aldebaran-linux-gnu/sysroot/usr/lib/librt.so
sdk/bin/a: /home/ruhtra/nao/ctc/boost/lib/libboost_date_time-mt-1_55.so
sdk/bin/a: /home/ruhtra/nao/ctc/boost/lib/libboost_system-mt-1_55.so
sdk/bin/a: /home/ruhtra/nao/ctc/boost/lib/libboost_locale-mt-1_55.so
sdk/bin/a: /home/ruhtra/nao/ctc/boost/lib/libboost_thread-mt-1_55.so
sdk/bin/a: /home/ruhtra/nao/ctc/cross/i686-aldebaran-linux-gnu/sysroot/usr/lib/libpthread.so
sdk/bin/a: /home/ruhtra/nao/ctc/connect4_rule/libc4rule.so
sdk/bin/a: CMakeFiles/a.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ruhtra/nao/naoqi-sdk/doc/dev/cpp/examples/core/Connect4_nao/build-ctc/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable sdk/bin/a"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/a.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/a.dir/build: sdk/bin/a

.PHONY : CMakeFiles/a.dir/build

CMakeFiles/a.dir/requires: CMakeFiles/a.dir/src/Main.cpp.o.requires
CMakeFiles/a.dir/requires: CMakeFiles/a.dir/src/Reactions.cpp.o.requires

.PHONY : CMakeFiles/a.dir/requires

CMakeFiles/a.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/a.dir/cmake_clean.cmake
.PHONY : CMakeFiles/a.dir/clean

CMakeFiles/a.dir/depend:
	cd /home/ruhtra/nao/naoqi-sdk/doc/dev/cpp/examples/core/Connect4_nao/build-ctc && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ruhtra/nao/naoqi-sdk/doc/dev/cpp/examples/core/Connect4_nao /home/ruhtra/nao/naoqi-sdk/doc/dev/cpp/examples/core/Connect4_nao /home/ruhtra/nao/naoqi-sdk/doc/dev/cpp/examples/core/Connect4_nao/build-ctc /home/ruhtra/nao/naoqi-sdk/doc/dev/cpp/examples/core/Connect4_nao/build-ctc /home/ruhtra/nao/naoqi-sdk/doc/dev/cpp/examples/core/Connect4_nao/build-ctc/CMakeFiles/a.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/a.dir/depend
