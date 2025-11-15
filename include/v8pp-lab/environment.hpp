#pragma once

#include <v8.h>
#include <v8pp/context.hpp>
#include <v8/libplatform/libplatform.h>
#include "v8pp/module.hpp"
#include "v8pp-lab/concepts.hpp"
#include "v8pp-lab/environment.hpp"

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

class V8ppEnvironment final
{
public:
    V8ppEnvironment():
        m_context(Context::createContext())
    {

    }
    template <CppModule Module>
    void addModule(Module& module)
    {
        v8pp::module v8Module = module.generateModule(m_context->isolate);
        m_context->context.module(module.name(), v8Module);
    }

    template <JSScript Script>
    void runScript(Script& script)
    {
        auto result = m_context->context.run_script(script.get());
        script.process(result, m_context->isolate);
    }
private:
    std::unique_ptr<Context> m_context {};
};


static_assert(ScriptEnvironment<V8ppEnvironment>, "Must adhere to 'ScriptEnvironment' concept!");
}
