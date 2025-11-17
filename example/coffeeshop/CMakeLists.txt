add_library(CoffeeShop SHARED
    include/coffeeshop/coffeeshopmodule.hpp

    src/simulation.hpp
    src/coffeeshopmodule.cpp
    src/coffeemachine.hpp
    src/mug.hpp
)


target_link_libraries(CoffeeShop
    PUBLIC
    V8ppLab)

target_include_directories(CoffeeShop
    PUBLIC
    include
    PRIVATE
    src)
