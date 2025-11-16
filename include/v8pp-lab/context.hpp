#pragma once

#include <v8.h>
#include <v8pp/context.hpp>
#include <v8/libplatform/libplatform.h>
#include "v8pp/module.hpp"
#include "v8pp-lab/concepts.hpp"

namespace V8ppLab
{

//!
//! \brief The context encapsulates the V8 initialzation and
//!        creation of a context and scope.
//!        As a result, while the V8Context instance is alive the
//!        associated ScopeHandle is as well.
//!
struct V8Context
{
    //!
    //! \brief Allows to create a instance of the class.
    //!        Note that the ownership lies with the caller of this
    //!        method.
    //!
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

    //!
    //! \brief V8 Context to run scripts and load cpp modules with.
    //!
    v8pp::context context;

    //!
    //! \brief V8 Isolate
    //!
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
