cmake_minimum_required(VERSION 3.7.1 FATAL_ERROR)

project(libtest)

find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

message(STATUS "binary directory: " ${PROJECT_BINARY_DIR})
message(STATUS "source directory: " ${PROJECT_SOURCE_DIR})

set(CMAKE_C_COMPILER "/usr/bin/clang-16")
set(CMAKE_CXX_COMPILER "/usr/bin/clang++-16")
set(CMAKE_CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-ggdb3")
set(CMAKE_CXX_FLAGS_RELEASE "-O4 -DNDEBUG")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_definitions("-DFMT_HEADER_ONLY")
add_definitions("-DDOCTEST_CONFIG_SUPER_FAST_ASSERTS")


message(STATUS "LLVM_INCLUDE_DIRS: " ${LLVM_INCLUDE_DIRS})
message(STATUS "LLVM_DEFINITIONS: " ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS})

include_directories(include)
include_directories(external)
include_directories(external/doctest)
include_directories(external/fmt/include)

add_subdirectory(tests)

# add_executable(test ${SRCS})




