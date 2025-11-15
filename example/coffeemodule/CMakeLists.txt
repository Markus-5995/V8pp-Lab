add_library(CoffeeModule SHARED
    include/coffeemodule/coffemodule.hpp
    src/coffeemodule.cpp)


target_link_libraries(CoffeeModule
    PUBLIC
    AppConcepts)

target_include_directories(CoffeeModule
    PUBLIC
    include
    PRIVATE
    src)
