#pragma once
#include "mug.hpp"
#include <vector>
#include "v8-data.h"
namespace CoffeeShop
{

struct CoffeeMachine
{
    void act()
    {
        for(Mug* mug : mugs)
        {
            if (mug == nullptr)
            {
                continue;
            }
            mug->fillStand += 10;
            mug->temperature += 5;
        }
    }
    void placeMug(Mug* mug)
    {
        mugs.push_back(mug);
    }

private:
    std::vector<Mug*> mugs {};

};

} // namespace CoffeeShop
