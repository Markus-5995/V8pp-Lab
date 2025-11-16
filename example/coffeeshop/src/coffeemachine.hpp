#pragma once
#include "mug.hpp"
#include <vector>
#include "v8-data.h"
namespace CoffeeShop
{

struct CoffeeMachine
{
    void placeMug(Mug* mug)
    {
        mugs.push_back(mug);
    }
    std::vector<Mug*> mugs {};
};

} // namespace CoffeeShop
