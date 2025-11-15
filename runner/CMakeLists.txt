add_library(Runner SHARED
    include/runner/runner.hpp
    src/runner.cpp
    src/v8ppenvironment.hpp src/v8ppenvironment.cpp
)


target_include_directories(Runner
    PUBLIC
    include)

target_link_libraries(Runner
    PUBLIC
    AppConcepts)
