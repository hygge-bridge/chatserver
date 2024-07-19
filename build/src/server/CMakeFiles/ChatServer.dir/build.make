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
CMAKE_SOURCE_DIR = /home/hygge/codes/projectCode/chatserver

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/hygge/codes/projectCode/chatserver/build

# Include any dependencies generated for this target.
include src/server/CMakeFiles/ChatServer.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/server/CMakeFiles/ChatServer.dir/compiler_depend.make

# Include the progress variables for this target.
include src/server/CMakeFiles/ChatServer.dir/progress.make

# Include the compile flags for this target's objects.
include src/server/CMakeFiles/ChatServer.dir/flags.make

src/server/CMakeFiles/ChatServer.dir/chatserver.cc.o: src/server/CMakeFiles/ChatServer.dir/flags.make
src/server/CMakeFiles/ChatServer.dir/chatserver.cc.o: ../src/server/chatserver.cc
src/server/CMakeFiles/ChatServer.dir/chatserver.cc.o: src/server/CMakeFiles/ChatServer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hygge/codes/projectCode/chatserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/server/CMakeFiles/ChatServer.dir/chatserver.cc.o"
	cd /home/hygge/codes/projectCode/chatserver/build/src/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/server/CMakeFiles/ChatServer.dir/chatserver.cc.o -MF CMakeFiles/ChatServer.dir/chatserver.cc.o.d -o CMakeFiles/ChatServer.dir/chatserver.cc.o -c /home/hygge/codes/projectCode/chatserver/src/server/chatserver.cc

src/server/CMakeFiles/ChatServer.dir/chatserver.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ChatServer.dir/chatserver.cc.i"
	cd /home/hygge/codes/projectCode/chatserver/build/src/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hygge/codes/projectCode/chatserver/src/server/chatserver.cc > CMakeFiles/ChatServer.dir/chatserver.cc.i

src/server/CMakeFiles/ChatServer.dir/chatserver.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ChatServer.dir/chatserver.cc.s"
	cd /home/hygge/codes/projectCode/chatserver/build/src/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hygge/codes/projectCode/chatserver/src/server/chatserver.cc -o CMakeFiles/ChatServer.dir/chatserver.cc.s

src/server/CMakeFiles/ChatServer.dir/chatservice.cc.o: src/server/CMakeFiles/ChatServer.dir/flags.make
src/server/CMakeFiles/ChatServer.dir/chatservice.cc.o: ../src/server/chatservice.cc
src/server/CMakeFiles/ChatServer.dir/chatservice.cc.o: src/server/CMakeFiles/ChatServer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hygge/codes/projectCode/chatserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/server/CMakeFiles/ChatServer.dir/chatservice.cc.o"
	cd /home/hygge/codes/projectCode/chatserver/build/src/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/server/CMakeFiles/ChatServer.dir/chatservice.cc.o -MF CMakeFiles/ChatServer.dir/chatservice.cc.o.d -o CMakeFiles/ChatServer.dir/chatservice.cc.o -c /home/hygge/codes/projectCode/chatserver/src/server/chatservice.cc

src/server/CMakeFiles/ChatServer.dir/chatservice.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ChatServer.dir/chatservice.cc.i"
	cd /home/hygge/codes/projectCode/chatserver/build/src/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hygge/codes/projectCode/chatserver/src/server/chatservice.cc > CMakeFiles/ChatServer.dir/chatservice.cc.i

src/server/CMakeFiles/ChatServer.dir/chatservice.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ChatServer.dir/chatservice.cc.s"
	cd /home/hygge/codes/projectCode/chatserver/build/src/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hygge/codes/projectCode/chatserver/src/server/chatservice.cc -o CMakeFiles/ChatServer.dir/chatservice.cc.s

src/server/CMakeFiles/ChatServer.dir/friendmodel.cc.o: src/server/CMakeFiles/ChatServer.dir/flags.make
src/server/CMakeFiles/ChatServer.dir/friendmodel.cc.o: ../src/server/friendmodel.cc
src/server/CMakeFiles/ChatServer.dir/friendmodel.cc.o: src/server/CMakeFiles/ChatServer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hygge/codes/projectCode/chatserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/server/CMakeFiles/ChatServer.dir/friendmodel.cc.o"
	cd /home/hygge/codes/projectCode/chatserver/build/src/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/server/CMakeFiles/ChatServer.dir/friendmodel.cc.o -MF CMakeFiles/ChatServer.dir/friendmodel.cc.o.d -o CMakeFiles/ChatServer.dir/friendmodel.cc.o -c /home/hygge/codes/projectCode/chatserver/src/server/friendmodel.cc

src/server/CMakeFiles/ChatServer.dir/friendmodel.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ChatServer.dir/friendmodel.cc.i"
	cd /home/hygge/codes/projectCode/chatserver/build/src/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hygge/codes/projectCode/chatserver/src/server/friendmodel.cc > CMakeFiles/ChatServer.dir/friendmodel.cc.i

src/server/CMakeFiles/ChatServer.dir/friendmodel.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ChatServer.dir/friendmodel.cc.s"
	cd /home/hygge/codes/projectCode/chatserver/build/src/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hygge/codes/projectCode/chatserver/src/server/friendmodel.cc -o CMakeFiles/ChatServer.dir/friendmodel.cc.s

src/server/CMakeFiles/ChatServer.dir/main.cc.o: src/server/CMakeFiles/ChatServer.dir/flags.make
src/server/CMakeFiles/ChatServer.dir/main.cc.o: ../src/server/main.cc
src/server/CMakeFiles/ChatServer.dir/main.cc.o: src/server/CMakeFiles/ChatServer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hygge/codes/projectCode/chatserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object src/server/CMakeFiles/ChatServer.dir/main.cc.o"
	cd /home/hygge/codes/projectCode/chatserver/build/src/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/server/CMakeFiles/ChatServer.dir/main.cc.o -MF CMakeFiles/ChatServer.dir/main.cc.o.d -o CMakeFiles/ChatServer.dir/main.cc.o -c /home/hygge/codes/projectCode/chatserver/src/server/main.cc

src/server/CMakeFiles/ChatServer.dir/main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ChatServer.dir/main.cc.i"
	cd /home/hygge/codes/projectCode/chatserver/build/src/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hygge/codes/projectCode/chatserver/src/server/main.cc > CMakeFiles/ChatServer.dir/main.cc.i

src/server/CMakeFiles/ChatServer.dir/main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ChatServer.dir/main.cc.s"
	cd /home/hygge/codes/projectCode/chatserver/build/src/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hygge/codes/projectCode/chatserver/src/server/main.cc -o CMakeFiles/ChatServer.dir/main.cc.s

src/server/CMakeFiles/ChatServer.dir/offlinemsgmodel.cc.o: src/server/CMakeFiles/ChatServer.dir/flags.make
src/server/CMakeFiles/ChatServer.dir/offlinemsgmodel.cc.o: ../src/server/offlinemsgmodel.cc
src/server/CMakeFiles/ChatServer.dir/offlinemsgmodel.cc.o: src/server/CMakeFiles/ChatServer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hygge/codes/projectCode/chatserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object src/server/CMakeFiles/ChatServer.dir/offlinemsgmodel.cc.o"
	cd /home/hygge/codes/projectCode/chatserver/build/src/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/server/CMakeFiles/ChatServer.dir/offlinemsgmodel.cc.o -MF CMakeFiles/ChatServer.dir/offlinemsgmodel.cc.o.d -o CMakeFiles/ChatServer.dir/offlinemsgmodel.cc.o -c /home/hygge/codes/projectCode/chatserver/src/server/offlinemsgmodel.cc

src/server/CMakeFiles/ChatServer.dir/offlinemsgmodel.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ChatServer.dir/offlinemsgmodel.cc.i"
	cd /home/hygge/codes/projectCode/chatserver/build/src/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hygge/codes/projectCode/chatserver/src/server/offlinemsgmodel.cc > CMakeFiles/ChatServer.dir/offlinemsgmodel.cc.i

src/server/CMakeFiles/ChatServer.dir/offlinemsgmodel.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ChatServer.dir/offlinemsgmodel.cc.s"
	cd /home/hygge/codes/projectCode/chatserver/build/src/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hygge/codes/projectCode/chatserver/src/server/offlinemsgmodel.cc -o CMakeFiles/ChatServer.dir/offlinemsgmodel.cc.s

src/server/CMakeFiles/ChatServer.dir/usermodel.cc.o: src/server/CMakeFiles/ChatServer.dir/flags.make
src/server/CMakeFiles/ChatServer.dir/usermodel.cc.o: ../src/server/usermodel.cc
src/server/CMakeFiles/ChatServer.dir/usermodel.cc.o: src/server/CMakeFiles/ChatServer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hygge/codes/projectCode/chatserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object src/server/CMakeFiles/ChatServer.dir/usermodel.cc.o"
	cd /home/hygge/codes/projectCode/chatserver/build/src/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/server/CMakeFiles/ChatServer.dir/usermodel.cc.o -MF CMakeFiles/ChatServer.dir/usermodel.cc.o.d -o CMakeFiles/ChatServer.dir/usermodel.cc.o -c /home/hygge/codes/projectCode/chatserver/src/server/usermodel.cc

src/server/CMakeFiles/ChatServer.dir/usermodel.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ChatServer.dir/usermodel.cc.i"
	cd /home/hygge/codes/projectCode/chatserver/build/src/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hygge/codes/projectCode/chatserver/src/server/usermodel.cc > CMakeFiles/ChatServer.dir/usermodel.cc.i

src/server/CMakeFiles/ChatServer.dir/usermodel.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ChatServer.dir/usermodel.cc.s"
	cd /home/hygge/codes/projectCode/chatserver/build/src/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hygge/codes/projectCode/chatserver/src/server/usermodel.cc -o CMakeFiles/ChatServer.dir/usermodel.cc.s

src/server/CMakeFiles/ChatServer.dir/db/db.cc.o: src/server/CMakeFiles/ChatServer.dir/flags.make
src/server/CMakeFiles/ChatServer.dir/db/db.cc.o: ../src/server/db/db.cc
src/server/CMakeFiles/ChatServer.dir/db/db.cc.o: src/server/CMakeFiles/ChatServer.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/hygge/codes/projectCode/chatserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object src/server/CMakeFiles/ChatServer.dir/db/db.cc.o"
	cd /home/hygge/codes/projectCode/chatserver/build/src/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/server/CMakeFiles/ChatServer.dir/db/db.cc.o -MF CMakeFiles/ChatServer.dir/db/db.cc.o.d -o CMakeFiles/ChatServer.dir/db/db.cc.o -c /home/hygge/codes/projectCode/chatserver/src/server/db/db.cc

src/server/CMakeFiles/ChatServer.dir/db/db.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ChatServer.dir/db/db.cc.i"
	cd /home/hygge/codes/projectCode/chatserver/build/src/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/hygge/codes/projectCode/chatserver/src/server/db/db.cc > CMakeFiles/ChatServer.dir/db/db.cc.i

src/server/CMakeFiles/ChatServer.dir/db/db.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ChatServer.dir/db/db.cc.s"
	cd /home/hygge/codes/projectCode/chatserver/build/src/server && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/hygge/codes/projectCode/chatserver/src/server/db/db.cc -o CMakeFiles/ChatServer.dir/db/db.cc.s

# Object files for target ChatServer
ChatServer_OBJECTS = \
"CMakeFiles/ChatServer.dir/chatserver.cc.o" \
"CMakeFiles/ChatServer.dir/chatservice.cc.o" \
"CMakeFiles/ChatServer.dir/friendmodel.cc.o" \
"CMakeFiles/ChatServer.dir/main.cc.o" \
"CMakeFiles/ChatServer.dir/offlinemsgmodel.cc.o" \
"CMakeFiles/ChatServer.dir/usermodel.cc.o" \
"CMakeFiles/ChatServer.dir/db/db.cc.o"

# External object files for target ChatServer
ChatServer_EXTERNAL_OBJECTS =

../bin/ChatServer: src/server/CMakeFiles/ChatServer.dir/chatserver.cc.o
../bin/ChatServer: src/server/CMakeFiles/ChatServer.dir/chatservice.cc.o
../bin/ChatServer: src/server/CMakeFiles/ChatServer.dir/friendmodel.cc.o
../bin/ChatServer: src/server/CMakeFiles/ChatServer.dir/main.cc.o
../bin/ChatServer: src/server/CMakeFiles/ChatServer.dir/offlinemsgmodel.cc.o
../bin/ChatServer: src/server/CMakeFiles/ChatServer.dir/usermodel.cc.o
../bin/ChatServer: src/server/CMakeFiles/ChatServer.dir/db/db.cc.o
../bin/ChatServer: src/server/CMakeFiles/ChatServer.dir/build.make
../bin/ChatServer: src/server/CMakeFiles/ChatServer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/hygge/codes/projectCode/chatserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable ../../../bin/ChatServer"
	cd /home/hygge/codes/projectCode/chatserver/build/src/server && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ChatServer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/server/CMakeFiles/ChatServer.dir/build: ../bin/ChatServer
.PHONY : src/server/CMakeFiles/ChatServer.dir/build

src/server/CMakeFiles/ChatServer.dir/clean:
	cd /home/hygge/codes/projectCode/chatserver/build/src/server && $(CMAKE_COMMAND) -P CMakeFiles/ChatServer.dir/cmake_clean.cmake
.PHONY : src/server/CMakeFiles/ChatServer.dir/clean

src/server/CMakeFiles/ChatServer.dir/depend:
	cd /home/hygge/codes/projectCode/chatserver/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hygge/codes/projectCode/chatserver /home/hygge/codes/projectCode/chatserver/src/server /home/hygge/codes/projectCode/chatserver/build /home/hygge/codes/projectCode/chatserver/build/src/server /home/hygge/codes/projectCode/chatserver/build/src/server/CMakeFiles/ChatServer.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/server/CMakeFiles/ChatServer.dir/depend

