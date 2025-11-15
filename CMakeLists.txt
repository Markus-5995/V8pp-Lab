cmake_minimum_required(VERSION 3.15)
project(JSRunner CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
add_compile_options("-fconcepts-diagnostics-depth=10")

find_package(v8pp REQUIRED)
find_package(V8 REQUIRED)

add_subdirectory(appconcepts)
add_subdirectory(runner)
add_subdirectory(jsprovider)
add_subdirectory(cppprovider)
add_subdirectory(coffeemodule)

add_executable(JSRunner
    src/main.cpp)

target_link_libraries(JSRunner
    PUBLIC
    Runner
    JSProvider
    CoffeeModule)

