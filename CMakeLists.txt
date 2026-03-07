cmake_minimum_required(VERSION 3.20)
project(LiteGDK LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
set(FETCHCONTENT_UPDATES_DISCONNECTED ON CACHE BOOL "" FORCE)

# raylib
FetchContent_Declare(
  raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib.git
  GIT_TAG        master
)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(raylib)

# Catch2
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.5.2
)
FetchContent_MakeAvailable(Catch2)

# Library target
add_library(litegdk
    src/compat/DarkGDK.cpp
    src/runtime/AppRuntime.cpp
    src/runtime/FrameState.cpp
)
target_include_directories(litegdk PUBLIC include)
target_include_directories(litegdk PRIVATE src)
target_link_libraries(litegdk PRIVATE raylib)

# Tests target
enable_testing()
add_executable(litegdk_tests
    tests/unit/runtime/test_runtime.cpp
)
target_include_directories(litegdk_tests PRIVATE src)
target_link_libraries(litegdk_tests PRIVATE litegdk Catch2::Catch2WithMain)
include(Catch)
catch_discover_tests(litegdk_tests)
