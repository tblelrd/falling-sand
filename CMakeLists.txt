cmake_minimum_required(VERSION 3.10) # Version of cmake.
project(FallingSand) # Name of project

set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # Create the compile_commands.json file
set(CMAKE_CXX_STANDARD 17) # CPP STANDARD

include(FetchContent) # Module that lets me download libraries.
FetchContent_Declare(
  raylib # Name of library.
  GIT_REPOSITORY https://github.com/raysan5/raylib.git # Git repo.
  GIT_TAG 5.5 # The version of the library.
)

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # Turn off build examples.
FetchContent_MakeAvailable(raylib) # Actually download the library.

file(GLOB_RECURSE SRC_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)

add_executable(FallingSand ${SRC_FILES}) # Compile the cpp.
# add_executable(FallingSand main.cpp) # Compile the cpp.
target_link_libraries(FallingSand raylib) # Link the library to the executable.
