# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.17

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
CMAKE_COMMAND = /snap/clion/137/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/137/bin/cmake/linux/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/michal/Desktop/tin/TIN_NFS/client

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/michal/Desktop/tin/TIN_NFS/client/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/client.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/client.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/client.dir/flags.make

CMakeFiles/client.dir/fileOperations.cpp.o: CMakeFiles/client.dir/flags.make
CMakeFiles/client.dir/fileOperations.cpp.o: ../fileOperations.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/michal/Desktop/tin/TIN_NFS/client/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/client.dir/fileOperations.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/client.dir/fileOperations.cpp.o -c /home/michal/Desktop/tin/TIN_NFS/client/fileOperations.cpp

CMakeFiles/client.dir/fileOperations.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client.dir/fileOperations.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/michal/Desktop/tin/TIN_NFS/client/fileOperations.cpp > CMakeFiles/client.dir/fileOperations.cpp.i

CMakeFiles/client.dir/fileOperations.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client.dir/fileOperations.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/michal/Desktop/tin/TIN_NFS/client/fileOperations.cpp -o CMakeFiles/client.dir/fileOperations.cpp.s

CMakeFiles/client.dir/main.cpp.o: CMakeFiles/client.dir/flags.make
CMakeFiles/client.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/michal/Desktop/tin/TIN_NFS/client/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/client.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/client.dir/main.cpp.o -c /home/michal/Desktop/tin/TIN_NFS/client/main.cpp

CMakeFiles/client.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/michal/Desktop/tin/TIN_NFS/client/main.cpp > CMakeFiles/client.dir/main.cpp.i

CMakeFiles/client.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/michal/Desktop/tin/TIN_NFS/client/main.cpp -o CMakeFiles/client.dir/main.cpp.s

CMakeFiles/client.dir/file/open/open.cpp.o: CMakeFiles/client.dir/flags.make
CMakeFiles/client.dir/file/open/open.cpp.o: ../file/open/open.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/michal/Desktop/tin/TIN_NFS/client/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/client.dir/file/open/open.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/client.dir/file/open/open.cpp.o -c /home/michal/Desktop/tin/TIN_NFS/client/file/open/open.cpp

CMakeFiles/client.dir/file/open/open.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client.dir/file/open/open.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/michal/Desktop/tin/TIN_NFS/client/file/open/open.cpp > CMakeFiles/client.dir/file/open/open.cpp.i

CMakeFiles/client.dir/file/open/open.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client.dir/file/open/open.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/michal/Desktop/tin/TIN_NFS/client/file/open/open.cpp -o CMakeFiles/client.dir/file/open/open.cpp.s

CMakeFiles/client.dir/authorization/authorization.cpp.o: CMakeFiles/client.dir/flags.make
CMakeFiles/client.dir/authorization/authorization.cpp.o: ../authorization/authorization.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/michal/Desktop/tin/TIN_NFS/client/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/client.dir/authorization/authorization.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/client.dir/authorization/authorization.cpp.o -c /home/michal/Desktop/tin/TIN_NFS/client/authorization/authorization.cpp

CMakeFiles/client.dir/authorization/authorization.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client.dir/authorization/authorization.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/michal/Desktop/tin/TIN_NFS/client/authorization/authorization.cpp > CMakeFiles/client.dir/authorization/authorization.cpp.i

CMakeFiles/client.dir/authorization/authorization.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client.dir/authorization/authorization.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/michal/Desktop/tin/TIN_NFS/client/authorization/authorization.cpp -o CMakeFiles/client.dir/authorization/authorization.cpp.s

CMakeFiles/client.dir/send_message/send_message.cpp.o: CMakeFiles/client.dir/flags.make
CMakeFiles/client.dir/send_message/send_message.cpp.o: ../send_message/send_message.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/michal/Desktop/tin/TIN_NFS/client/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/client.dir/send_message/send_message.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/client.dir/send_message/send_message.cpp.o -c /home/michal/Desktop/tin/TIN_NFS/client/send_message/send_message.cpp

CMakeFiles/client.dir/send_message/send_message.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/client.dir/send_message/send_message.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/michal/Desktop/tin/TIN_NFS/client/send_message/send_message.cpp > CMakeFiles/client.dir/send_message/send_message.cpp.i

CMakeFiles/client.dir/send_message/send_message.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/client.dir/send_message/send_message.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/michal/Desktop/tin/TIN_NFS/client/send_message/send_message.cpp -o CMakeFiles/client.dir/send_message/send_message.cpp.s

# Object files for target client
client_OBJECTS = \
"CMakeFiles/client.dir/fileOperations.cpp.o" \
"CMakeFiles/client.dir/main.cpp.o" \
"CMakeFiles/client.dir/file/open/open.cpp.o" \
"CMakeFiles/client.dir/authorization/authorization.cpp.o" \
"CMakeFiles/client.dir/send_message/send_message.cpp.o"

# External object files for target client
client_EXTERNAL_OBJECTS =

client: CMakeFiles/client.dir/fileOperations.cpp.o
client: CMakeFiles/client.dir/main.cpp.o
client: CMakeFiles/client.dir/file/open/open.cpp.o
client: CMakeFiles/client.dir/authorization/authorization.cpp.o
client: CMakeFiles/client.dir/send_message/send_message.cpp.o
client: CMakeFiles/client.dir/build.make
client: CMakeFiles/client.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/michal/Desktop/tin/TIN_NFS/client/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable client"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/client.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/client.dir/build: client

.PHONY : CMakeFiles/client.dir/build

CMakeFiles/client.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/client.dir/cmake_clean.cmake
.PHONY : CMakeFiles/client.dir/clean

CMakeFiles/client.dir/depend:
	cd /home/michal/Desktop/tin/TIN_NFS/client/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/michal/Desktop/tin/TIN_NFS/client /home/michal/Desktop/tin/TIN_NFS/client /home/michal/Desktop/tin/TIN_NFS/client/cmake-build-debug /home/michal/Desktop/tin/TIN_NFS/client/cmake-build-debug /home/michal/Desktop/tin/TIN_NFS/client/cmake-build-debug/CMakeFiles/client.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/client.dir/depend

