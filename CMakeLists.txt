cmake_minimum_required(VERSION 3.15)
project(V8ppLab CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(BUILD_EXAMPLE "Builds the example exectuable" ON)

find_package(v8pp REQUIRED)
find_package(V8 REQUIRED)

if(BUILD_EXAMPLE)
    add_subdirectory(example)
endif()

add_library(V8ppLab INTERFACE
    include/v8pp-lab/runner.hpp
    include/v8pp-lab/context.hpp
    include/v8pp-lab/concepts.hpp
    include/v8pp-lab/filelocator.hpp
    include/v8pp-lab/scripts.hpp)


target_include_directories(V8ppLab
    INTERFACE
    include)

target_link_libraries(V8ppLab
    INTERFACE
    v8pp::v8pp)

