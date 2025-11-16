#pragma once
#include "coffeemachine.hpp"
namespace CoffeeShop
{
class Simulation
{
public:
    Simulation(CoffeeMachine* machine) :
        m_machine(machine)
    {

    }
    void run()
    {
        if (m_machine == nullptr)
        {
            return;
        }
        bool exitCondition {};
        while (! exitCondition)
        {
            for(Mug* mug : m_machine->mugs)
            {
                if (mug == nullptr)
                {
                    continue;
                }
                mug->fillStand += 10;
                mug->temperature += 5;
                exitCondition = mug->full();
            }
            m_runtime++;
        }
    }
    int runtime() const
    {
        return m_runtime;
    }

private:
    int m_runtime {};
    CoffeeMachine* m_machine;
};

} // namespace CoffeeShop
