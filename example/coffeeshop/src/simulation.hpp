#pragma once
#include "coffeemachine.hpp"
#include "v8pp/call_v8.hpp"
namespace CoffeeShop
{
class Simulation
{
public:
    Simulation(CoffeeMachine* machine) :
        m_machine(machine)
    {

    }
    void run(v8::Local<v8::Function> function)
    {
        if (m_machine == nullptr)
        {
            return;
        }

        auto* currentIsolate = v8::Isolate::GetCurrent();
        while (! endConditionMet(function, currentIsolate))
        {
            m_machine->act();
            m_runtime++;
        }
    }
    int runtime() const
    {
        return m_runtime;
    }

private:
    bool endConditionMet(v8::Local<v8::Function>& function, v8::Isolate* isolate)
    {
        auto context = isolate->GetCurrentContext();
        v8::Local<v8::Value> recv = context->Global();

        v8::Local<v8::Value> result = v8pp::call_v8(isolate, function, recv);
        if (! result.IsEmpty())
        {
            return v8pp::from_v8<bool>(isolate, result);
        }
        return true;
    }


    int m_runtime {};
    CoffeeMachine* m_machine;
};

} // namespace CoffeeShop
