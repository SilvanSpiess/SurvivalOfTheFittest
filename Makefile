# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.23

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:

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
CMAKE_COMMAND = /usr/bin/cmake.exe

# The command to remove a file.
RM = /usr/bin/cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/cygdrive/c/Users/silsp/Downloads/wotf github/SurvivalOfTheFittest"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/cygdrive/c/Users/silsp/Downloads/wotf github/SurvivalOfTheFittest"

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/usr/bin/ccmake.exe -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake.exe --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start "/cygdrive/c/Users/silsp/Downloads/wotf github/SurvivalOfTheFittest/CMakeFiles" "/cygdrive/c/Users/silsp/Downloads/wotf github/SurvivalOfTheFittest//CMakeFiles/progress.marks"
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start "/cygdrive/c/Users/silsp/Downloads/wotf github/SurvivalOfTheFittest/CMakeFiles" 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named fittest

# Build rule for target.
fittest: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 fittest
.PHONY : fittest

# fast build rule for target.
fittest/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/fittest.dir/build.make CMakeFiles/fittest.dir/build
.PHONY : fittest/fast

src/Engine.o: src/Engine.cpp.o
.PHONY : src/Engine.o

# target to build an object file
src/Engine.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/fittest.dir/build.make CMakeFiles/fittest.dir/src/Engine.cpp.o
.PHONY : src/Engine.cpp.o

src/Engine.i: src/Engine.cpp.i
.PHONY : src/Engine.i

# target to preprocess a source file
src/Engine.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/fittest.dir/build.make CMakeFiles/fittest.dir/src/Engine.cpp.i
.PHONY : src/Engine.cpp.i

src/Engine.s: src/Engine.cpp.s
.PHONY : src/Engine.s

# target to generate assembly for a file
src/Engine.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/fittest.dir/build.make CMakeFiles/fittest.dir/src/Engine.cpp.s
.PHONY : src/Engine.cpp.s

src/FileHandler.o: src/FileHandler.cpp.o
.PHONY : src/FileHandler.o

# target to build an object file
src/FileHandler.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/fittest.dir/build.make CMakeFiles/fittest.dir/src/FileHandler.cpp.o
.PHONY : src/FileHandler.cpp.o

src/FileHandler.i: src/FileHandler.cpp.i
.PHONY : src/FileHandler.i

# target to preprocess a source file
src/FileHandler.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/fittest.dir/build.make CMakeFiles/fittest.dir/src/FileHandler.cpp.i
.PHONY : src/FileHandler.cpp.i

src/FileHandler.s: src/FileHandler.cpp.s
.PHONY : src/FileHandler.s

# target to generate assembly for a file
src/FileHandler.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/fittest.dir/build.make CMakeFiles/fittest.dir/src/FileHandler.cpp.s
.PHONY : src/FileHandler.cpp.s

src/Living.o: src/Living.cpp.o
.PHONY : src/Living.o

# target to build an object file
src/Living.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/fittest.dir/build.make CMakeFiles/fittest.dir/src/Living.cpp.o
.PHONY : src/Living.cpp.o

src/Living.i: src/Living.cpp.i
.PHONY : src/Living.i

# target to preprocess a source file
src/Living.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/fittest.dir/build.make CMakeFiles/fittest.dir/src/Living.cpp.i
.PHONY : src/Living.cpp.i

src/Living.s: src/Living.cpp.s
.PHONY : src/Living.s

# target to generate assembly for a file
src/Living.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/fittest.dir/build.make CMakeFiles/fittest.dir/src/Living.cpp.s
.PHONY : src/Living.cpp.s

src/ProjectHandler.o: src/ProjectHandler.cpp.o
.PHONY : src/ProjectHandler.o

# target to build an object file
src/ProjectHandler.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/fittest.dir/build.make CMakeFiles/fittest.dir/src/ProjectHandler.cpp.o
.PHONY : src/ProjectHandler.cpp.o

src/ProjectHandler.i: src/ProjectHandler.cpp.i
.PHONY : src/ProjectHandler.i

# target to preprocess a source file
src/ProjectHandler.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/fittest.dir/build.make CMakeFiles/fittest.dir/src/ProjectHandler.cpp.i
.PHONY : src/ProjectHandler.cpp.i

src/ProjectHandler.s: src/ProjectHandler.cpp.s
.PHONY : src/ProjectHandler.s

# target to generate assembly for a file
src/ProjectHandler.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/fittest.dir/build.make CMakeFiles/fittest.dir/src/ProjectHandler.cpp.s
.PHONY : src/ProjectHandler.cpp.s

src/main.o: src/main.cpp.o
.PHONY : src/main.o

# target to build an object file
src/main.cpp.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/fittest.dir/build.make CMakeFiles/fittest.dir/src/main.cpp.o
.PHONY : src/main.cpp.o

src/main.i: src/main.cpp.i
.PHONY : src/main.i

# target to preprocess a source file
src/main.cpp.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/fittest.dir/build.make CMakeFiles/fittest.dir/src/main.cpp.i
.PHONY : src/main.cpp.i

src/main.s: src/main.cpp.s
.PHONY : src/main.s

# target to generate assembly for a file
src/main.cpp.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/fittest.dir/build.make CMakeFiles/fittest.dir/src/main.cpp.s
.PHONY : src/main.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... fittest"
	@echo "... src/Engine.o"
	@echo "... src/Engine.i"
	@echo "... src/Engine.s"
	@echo "... src/FileHandler.o"
	@echo "... src/FileHandler.i"
	@echo "... src/FileHandler.s"
	@echo "... src/Living.o"
	@echo "... src/Living.i"
	@echo "... src/Living.s"
	@echo "... src/ProjectHandler.o"
	@echo "... src/ProjectHandler.i"
	@echo "... src/ProjectHandler.s"
	@echo "... src/main.o"
	@echo "... src/main.i"
	@echo "... src/main.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

