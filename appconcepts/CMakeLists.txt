add_library(AppConcepts INTERFACE)

target_include_directories(AppConcepts
    INTERFACE
    include)
target_link_libraries (AppConcepts
    INTERFACE
    v8pp::v8pp)

add_library(__IDE_HELPER STATIC EXCLUDE_FROM_ALL
    include/appconcepts/cppmodule.hpp
    include/appconcepts/script.hpp)

set_target_properties(__IDE_HELPER PROPERTIES LINKER_LANGUAGE CXX)

