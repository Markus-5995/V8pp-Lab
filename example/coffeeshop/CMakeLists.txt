add_library(CoffeeShop SHARED
    include/coffeeshop/coffeeshopmodule.hpp
    src/simulation.cpp
    src/simulation.hpp
    src/coffeeshopmodule.cpp
    src/coffeemachine.hpp src/coffeemachine.cpp
    src/mug.hpp src/mug.cpp
)


target_link_libraries(CoffeeShop
    PUBLIC
    V8ppLab)

target_include_directories(CoffeeShop
    PUBLIC
    include
    PRIVATE
    src)
