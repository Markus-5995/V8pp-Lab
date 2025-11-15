#pragma once
#include "v8pp/module.hpp"
#include "v8-data.h"
#include "concepts"
namespace V8ppLab
{

template<typename T>
concept JSScript = requires(T t,
                            v8::Local<v8::Value> result,
                            v8::Isolate* isolate)
{
    {t.get()} -> std::convertible_to<std::string_view>;
    {t.name()} -> std::convertible_to<std::string_view>;
    t.process(result, isolate);

};

template<typename T>
concept CppModule = requires(T t,
                             v8::Isolate* isolate)
{
    { t.generateModule(isolate) } -> std::same_as<v8pp::module>;
    { t.name() } -> std::convertible_to<std::string_view>;
};

template<typename Environment>
concept ScriptEnvironment =
    requires(Environment env)
{
    &Environment::template addModule<CppModule auto>;
    &Environment::template runScript<JSScript auto>;
};

}
