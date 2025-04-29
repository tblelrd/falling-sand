cmake_minimum_required(VERSION 3.10)
project(FallingSand)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)
FetchContent_Declare(
  raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib.git
  GIT_TAG 5.5
)

# Let raylib build as a static library
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(raylib)

add_executable(FallingSand main.cpp)
target_link_libraries(FallingSand raylib)
