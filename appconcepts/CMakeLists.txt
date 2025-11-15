add_library(AppConcepts INTERFACE)

target_include_directories(AppConcepts
    INTERFACE
    include)
target_link_libraries (AppConcepts
    INTERFACE
    v8pp::v8pp)


add_library(__IDE_HELPER_CONCEPTS INTERFACE
    include/appconcepts/cppmodule.hpp
    include/appconcepts/script.hpp)

