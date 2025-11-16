#pragma once

#include <v8.h>
#include <v8pp/context.hpp>
#include <v8/libplatform/libplatform.h>
#include "v8pp/module.hpp"
#include "v8pp-lab/concepts.hpp"

namespace V8ppLab
{

struct V8Context
{
    static V8Context* createContext()
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
        return new V8Context();
    }

    v8pp::context context;
    v8::Isolate* isolate;

private:
    v8::HandleScope scope;

    V8Context() :
        context(),
        isolate(context.isolate()),
        scope(isolate)
    {
    }
};
static_assert(ScriptContext<V8Context>, "Must adhere to 'ScriptContext' concept!");
}
