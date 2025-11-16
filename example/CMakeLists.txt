add_subdirectory(coffeemodule)
add_subdirectory(jstestfiles)

option(ENABLE_SANITIZERS "Enables ASAN for example." ON)

add_executable(Example
    main.cpp)

target_link_libraries(Example
    PUBLIC
    CoffeeModule)

target_compile_definitions(Example
    PRIVATE
    DEFAULT_JS_DIR="${CMAKE_CURRENT_SOURCE_DIR}/jstestfiles"
)

# Enable ASan in Debug mode
if (ENABLE_SANITIZERS)
    message(STATUS "Enabling AddressSanitizer")
    target_compile_options(Example PRIVATE -fsanitize=address -fno-omit-frame-pointer)
    target_link_options(Example PRIVATE -fsanitize=address)
endif()
