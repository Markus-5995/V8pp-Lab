add_subdirectory(coffeemodule)
add_subdirectory(jstestfiles)

add_executable(Example
    main.cpp)

target_link_libraries(Example
    PUBLIC
    CoffeeModule)

target_compile_definitions(Example
    PRIVATE
    DEFAULT_JS_DIR="${CMAKE_CURRENT_SOURCE_DIR}/jstestfiles"
)
