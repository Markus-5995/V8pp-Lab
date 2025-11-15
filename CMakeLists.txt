cmake_minimum_required(VERSION 3.15)
project(V8ppLab CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(BUILD_EXAMPLE ON)

find_package(v8pp REQUIRED)
find_package(V8 REQUIRED)

if(BUILD_EXAMPLE)
    add_subdirectory(example)
endif()


add_library(V8ppLab SHARED
    include/v8pp-lab/runner.hpp
    include/v8pp-lab/environment.hpp
    include/v8pp-lab/concepts.hpp
    include/v8pp-lab/filelocator.hpp
    include/v8pp-lab/scripts.hpp

    src/environment.cpp
    src/filelocator.cpp
    src/scripts.cpp
)

target_include_directories(V8ppLab
    PUBLIC
    include)

target_link_libraries(V8ppLab
    PUBLIC
    v8pp::v8pp)

