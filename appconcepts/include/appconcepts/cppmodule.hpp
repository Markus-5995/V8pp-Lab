#pragma once
#include "v8pp/module.hpp"
#include "concepts"
namespace AppConcepts
{
template<typename T>
concept CppModule = requires(T t,
                             v8::Isolate* isolate)
{
    { t.generateModule(isolate) } -> std::same_as<v8pp::module>;
    { t.name() } -> std::convertible_to<std::string_view>;
};


template<typename T>
concept ScriptEnvironment = requires(T t,
                                     std::string_view script,
                                     std::string_view name,
                                     v8pp::module module)
{

    { t.getContext() } -> std::same_as<v8::Isolate*>;
    t.addModule(name, std::move(module));
    t.runScript(script);
};

}
