#include "v8pp-lab/environment.hpp"
#include <v8.h>
#include <v8pp/context.hpp>
#include <v8/libplatform/libplatform.h>
#include <iostream>
namespace V8ppLab
{

struct Context
{
    static Context* createContext()
    {
        static bool v8Initialized {};
        if (! v8Initialized)
        {
            // Initialize V8
            v8::V8::InitializeICUDefaultLocation(nullptr);
            v8::V8::InitializeExternalStartupData(nullptr);

            v8::Platform* platform = v8::platform::NewDefaultPlatform().release();
            v8::V8::InitializePlatform(platform);
            v8::V8::Initialize();
            v8Initialized = true;
        }
        return new Context();
    }

    v8pp::context context;
    v8::Isolate* isolate;
    v8::HandleScope scope;
    v8::Local<v8::Context> ctx;

private:
    Context() :
        context(),
        isolate(context.isolate()),
        scope(isolate),
        ctx(context.impl())
    {
    }
};


V8ppEnvironment::V8ppEnvironment() :
    m_context(Context::createContext())
{

}

V8ppEnvironment::~V8ppEnvironment() = default;

v8::Isolate *V8ppEnvironment::getContext()
{
    return m_context->isolate;
}

void V8ppEnvironment::addModule(std::string_view name, v8pp::module &&module)
{
    m_context->context.module(name, module);
}

void V8ppEnvironment::runScript(std::string_view script)
{
    auto result = m_context->context.run_script(script);
    // Convert result to a C++ string and print it
    v8::String::Utf8Value utf8(m_context->isolate, result);
    std::cout << *utf8 << std::endl;
}

}
