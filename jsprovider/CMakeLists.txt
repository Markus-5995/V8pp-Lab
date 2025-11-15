add_library(JSProvider SHARED
    include/jsprovider/scripts.hpp
    src/scripts.cpp
    include/jsprovider/filelocator.hpp src/filelocator.cpp)

target_include_directories(JSProvider
    PUBLIC
    include)

target_link_libraries(JSProvider
    PUBLIC
    AppConcepts)
