#pragma once
#include "v8pp-lab/concepts.hpp"

namespace CppModule
{
class CoffeeModule
{
public:
    v8pp::module generateModule(v8::Isolate* isolate) const
    {
        v8pp::module m(isolate);
        m.const_("MagicTemperature", 42);
        return m;
    }
    std::string_view name() const
    {
        return "Coffee";
    }
};

static_assert(V8ppLap::CppModule<CoffeeModule>, "Must adhere to CppModule concept!");
}
