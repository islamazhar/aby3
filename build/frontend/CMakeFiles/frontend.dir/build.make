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
CMAKE_COMMAND = /home/mazharul/.local/lib/python3.8/site-packages/cmake/data/bin/cmake

# The command to remove a file.
RM = /home/mazharul/.local/lib/python3.8/site-packages/cmake/data/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/c/Users/Mazharul.Dell-Precision/Google-Drive/Research/Visa-Research/aby3

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Users/Mazharul.Dell-Precision/Google-Drive/Research/Visa-Research/aby3/build

# Include any dependencies generated for this target.
include frontend/CMakeFiles/frontend.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include frontend/CMakeFiles/frontend.dir/compiler_depend.make

# Include the progress variables for this target.
include frontend/CMakeFiles/frontend.dir/progress.make

# Include the compile flags for this target's objects.
include frontend/CMakeFiles/frontend.dir/flags.make

frontend/CMakeFiles/frontend.dir/aby3-DB-main.cpp.o: frontend/CMakeFiles/frontend.dir/flags.make
frontend/CMakeFiles/frontend.dir/aby3-DB-main.cpp.o: ../frontend/aby3-DB-main.cpp
frontend/CMakeFiles/frontend.dir/aby3-DB-main.cpp.o: frontend/CMakeFiles/frontend.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Mazharul.Dell-Precision/Google-Drive/Research/Visa-Research/aby3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object frontend/CMakeFiles/frontend.dir/aby3-DB-main.cpp.o"
	cd /mnt/c/Users/Mazharul.Dell-Precision/Google-Drive/Research/Visa-Research/aby3/build/frontend && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT frontend/CMakeFiles/frontend.dir/aby3-DB-main.cpp.o -MF CMakeFiles/frontend.dir/aby3-DB-main.cpp.o.d -o CMakeFiles/frontend.dir/aby3-DB-main.cpp.o -c /mnt/c/Users/Mazharul.Dell-Precision/Google-Drive/Research/Visa-Research/aby3/frontend/aby3-DB-main.cpp

frontend/CMakeFiles/frontend.dir/aby3-DB-main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/frontend.dir/aby3-DB-main.cpp.i"
	cd /mnt/c/Users/Mazharul.Dell-Precision/Google-Drive/Research/Visa-Research/aby3/build/frontend && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/Mazharul.Dell-Precision/Google-Drive/Research/Visa-Research/aby3/frontend/aby3-DB-main.cpp > CMakeFiles/frontend.dir/aby3-DB-main.cpp.i

frontend/CMakeFiles/frontend.dir/aby3-DB-main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/frontend.dir/aby3-DB-main.cpp.s"
	cd /mnt/c/Users/Mazharul.Dell-Precision/Google-Drive/Research/Visa-Research/aby3/build/frontend && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/Mazharul.Dell-Precision/Google-Drive/Research/Visa-Research/aby3/frontend/aby3-DB-main.cpp -o CMakeFiles/frontend.dir/aby3-DB-main.cpp.s

frontend/CMakeFiles/frontend.dir/aby3Tutorial.cpp.o: frontend/CMakeFiles/frontend.dir/flags.make
frontend/CMakeFiles/frontend.dir/aby3Tutorial.cpp.o: ../frontend/aby3Tutorial.cpp
frontend/CMakeFiles/frontend.dir/aby3Tutorial.cpp.o: frontend/CMakeFiles/frontend.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Mazharul.Dell-Precision/Google-Drive/Research/Visa-Research/aby3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object frontend/CMakeFiles/frontend.dir/aby3Tutorial.cpp.o"
	cd /mnt/c/Users/Mazharul.Dell-Precision/Google-Drive/Research/Visa-Research/aby3/build/frontend && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT frontend/CMakeFiles/frontend.dir/aby3Tutorial.cpp.o -MF CMakeFiles/frontend.dir/aby3Tutorial.cpp.o.d -o CMakeFiles/frontend.dir/aby3Tutorial.cpp.o -c /mnt/c/Users/Mazharul.Dell-Precision/Google-Drive/Research/Visa-Research/aby3/frontend/aby3Tutorial.cpp

frontend/CMakeFiles/frontend.dir/aby3Tutorial.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/frontend.dir/aby3Tutorial.cpp.i"
	cd /mnt/c/Users/Mazharul.Dell-Precision/Google-Drive/Research/Visa-Research/aby3/build/frontend && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/Mazharul.Dell-Precision/Google-Drive/Research/Visa-Research/aby3/frontend/aby3Tutorial.cpp > CMakeFiles/frontend.dir/aby3Tutorial.cpp.i

frontend/CMakeFiles/frontend.dir/aby3Tutorial.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/frontend.dir/aby3Tutorial.cpp.s"
	cd /mnt/c/Users/Mazharul.Dell-Precision/Google-Drive/Research/Visa-Research/aby3/build/frontend && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/Mazharul.Dell-Precision/Google-Drive/Research/Visa-Research/aby3/frontend/aby3Tutorial.cpp -o CMakeFiles/frontend.dir/aby3Tutorial.cpp.s

frontend/CMakeFiles/frontend.dir/eric.cpp.o: frontend/CMakeFiles/frontend.dir/flags.make
frontend/CMakeFiles/frontend.dir/eric.cpp.o: ../frontend/eric.cpp
frontend/CMakeFiles/frontend.dir/eric.cpp.o: frontend/CMakeFiles/frontend.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Mazharul.Dell-Precision/Google-Drive/Research/Visa-Research/aby3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object frontend/CMakeFiles/frontend.dir/eric.cpp.o"
	cd /mnt/c/Users/Mazharul.Dell-Precision/Google-Drive/Research/Visa-Research/aby3/build/frontend && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT frontend/CMakeFiles/frontend.dir/eric.cpp.o -MF CMakeFiles/frontend.dir/eric.cpp.o.d -o CMakeFiles/frontend.dir/eric.cpp.o -c /mnt/c/Users/Mazharul.Dell-Precision/Google-Drive/Research/Visa-Research/aby3/frontend/eric.cpp

frontend/CMakeFiles/frontend.dir/eric.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/frontend.dir/eric.cpp.i"
	cd /mnt/c/Users/Mazharul.Dell-Precision/Google-Drive/Research/Visa-Research/aby3/build/frontend && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/Mazharul.Dell-Precision/Google-Drive/Research/Visa-Research/aby3/frontend/eric.cpp > CMakeFiles/frontend.dir/eric.cpp.i

frontend/CMakeFiles/frontend.dir/eric.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/frontend.dir/eric.cpp.s"
	cd /mnt/c/Users/Mazharul.Dell-Precision/Google-Drive/Research/Visa-Research/aby3/build/frontend && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/Mazharul.Dell-Precision/Google-Drive/Research/Visa-Research/aby3/frontend/eric.cpp -o CMakeFiles/frontend.dir/eric.cpp.s

frontend/CMakeFiles/frontend.dir/main.cpp.o: frontend/CMakeFiles/frontend.dir/flags.make
frontend/CMakeFiles/frontend.dir/main.cpp.o: ../frontend/main.cpp
frontend/CMakeFiles/frontend.dir/main.cpp.o: frontend/CMakeFiles/frontend.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Users/Mazharul.Dell-Precision/Google-Drive/Research/Visa-Research/aby3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object frontend/CMakeFiles/frontend.dir/main.cpp.o"
	cd /mnt/c/Users/Mazharul.Dell-Precision/Google-Drive/Research/Visa-Research/aby3/build/frontend && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT frontend/CMakeFiles/frontend.dir/main.cpp.o -MF CMakeFiles/frontend.dir/main.cpp.o.d -o CMakeFiles/frontend.dir/main.cpp.o -c /mnt/c/Users/Mazharul.Dell-Precision/Google-Drive/Research/Visa-Research/aby3/frontend/main.cpp

frontend/CMakeFiles/frontend.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/frontend.dir/main.cpp.i"
	cd /mnt/c/Users/Mazharul.Dell-Precision/Google-Drive/Research/Visa-Research/aby3/build/frontend && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Users/Mazharul.Dell-Precision/Google-Drive/Research/Visa-Research/aby3/frontend/main.cpp > CMakeFiles/frontend.dir/main.cpp.i

frontend/CMakeFiles/frontend.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/frontend.dir/main.cpp.s"
	cd /mnt/c/Users/Mazharul.Dell-Precision/Google-Drive/Research/Visa-Research/aby3/build/frontend && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Users/Mazharul.Dell-Precision/Google-Drive/Research/Visa-Research/aby3/frontend/main.cpp -o CMakeFiles/frontend.dir/main.cpp.s

# Object files for target frontend
frontend_OBJECTS = \
"CMakeFiles/frontend.dir/aby3-DB-main.cpp.o" \
"CMakeFiles/frontend.dir/aby3Tutorial.cpp.o" \
"CMakeFiles/frontend.dir/eric.cpp.o" \
"CMakeFiles/frontend.dir/main.cpp.o"

# External object files for target frontend
frontend_EXTERNAL_OBJECTS =

../bin/frontend: frontend/CMakeFiles/frontend.dir/aby3-DB-main.cpp.o
../bin/frontend: frontend/CMakeFiles/frontend.dir/aby3Tutorial.cpp.o
../bin/frontend: frontend/CMakeFiles/frontend.dir/eric.cpp.o
../bin/frontend: frontend/CMakeFiles/frontend.dir/main.cpp.o
../bin/frontend: frontend/CMakeFiles/frontend.dir/build.make
../bin/frontend: ../lib/libcom-psi.a
../bin/frontend: ../lib/libaby3-ML.a
../bin/frontend: ../lib/libcom-psi_Tests.a
../bin/frontend: ../lib/libaby3_Tests.a
../bin/frontend: ../thirdparty/unix/lib/libtests_cryptoTools.a
../bin/frontend: ../lib/libcom-psi.a
../bin/frontend: ../lib/libaby3.a
../bin/frontend: ../thirdparty/unix/lib/liblibOTe.a
../bin/frontend: ../thirdparty/unix/lib/libcryptoTools.a
../bin/frontend: ../thirdparty/unix/lib/libboost_system.so.1.75.0
../bin/frontend: ../thirdparty/unix/lib/libboost_thread.so.1.75.0
../bin/frontend: frontend/CMakeFiles/frontend.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Users/Mazharul.Dell-Precision/Google-Drive/Research/Visa-Research/aby3/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX executable ../../bin/frontend"
	cd /mnt/c/Users/Mazharul.Dell-Precision/Google-Drive/Research/Visa-Research/aby3/build/frontend && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/frontend.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
frontend/CMakeFiles/frontend.dir/build: ../bin/frontend
.PHONY : frontend/CMakeFiles/frontend.dir/build

frontend/CMakeFiles/frontend.dir/clean:
	cd /mnt/c/Users/Mazharul.Dell-Precision/Google-Drive/Research/Visa-Research/aby3/build/frontend && $(CMAKE_COMMAND) -P CMakeFiles/frontend.dir/cmake_clean.cmake
.PHONY : frontend/CMakeFiles/frontend.dir/clean

frontend/CMakeFiles/frontend.dir/depend:
	cd /mnt/c/Users/Mazharul.Dell-Precision/Google-Drive/Research/Visa-Research/aby3/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Users/Mazharul.Dell-Precision/Google-Drive/Research/Visa-Research/aby3 /mnt/c/Users/Mazharul.Dell-Precision/Google-Drive/Research/Visa-Research/aby3/frontend /mnt/c/Users/Mazharul.Dell-Precision/Google-Drive/Research/Visa-Research/aby3/build /mnt/c/Users/Mazharul.Dell-Precision/Google-Drive/Research/Visa-Research/aby3/build/frontend /mnt/c/Users/Mazharul.Dell-Precision/Google-Drive/Research/Visa-Research/aby3/build/frontend/CMakeFiles/frontend.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : frontend/CMakeFiles/frontend.dir/depend
