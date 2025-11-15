#pragma once
#include "v8pp/module.hpp"
#include "appconcepts/cppmodule.hpp"


namespace Runner
{
class Context;
class V8ppEnvironment
{
public:
    V8ppEnvironment();
    ~V8ppEnvironment();
    v8::Isolate* getContext();
    void addModule(std::string_view name, v8pp::module&& module);
    void runScript(std::string_view script);
private:
    std::unique_ptr<Context> m_context {};
};


static_assert(AppConcepts::ScriptEnvironment<V8ppEnvironment>, "Must adhere to 'ScriptEnvironment' concept!");
}
