#pragma once
#include "v8pp/module.hpp"
#include "v8pp/context.hpp"
#include "v8-data.h"
#include <concepts>
namespace V8ppLab
{

//!
//! \brief This concept describes how js scripts are
//!        supposed to look like.
//!
template<typename T>
concept JSScript = requires(T t,
                            v8::Local<v8::Value> result,
                            v8::Isolate* isolate)
{
    {t.get()} -> std::convertible_to<std::string_view>;
    {t.name()} -> std::convertible_to<std::string_view>;
    t.process(result, isolate);

};

//!
//! \brief This concept describes how cpp modules are
//!        supposed to look like.
//!
template<typename T>
concept CppModule = requires(T t,
                             v8::Isolate* isolate)
{
    { t.generateModule(isolate) } -> std::same_as<v8pp::module>;
    { t.name() } -> std::convertible_to<std::string_view>;
};


//!
//! \brief This concpet describes how a script context is
//!        supposed to look like.
//!
template<typename T>
concept ScriptContext = requires(T t)
{
    { T::createContext() } -> std::same_as<T*>;
    { t.context } -> std::convertible_to<v8pp::context&>;
    { t.isolate } -> std::convertible_to<v8::Isolate*>;
};

}
