#pragma once
#include "v8pp-lab/concepts.hpp"
#include <vector>
#include <tuple>
#include <iostream>
namespace V8ppLab
{

//!
//! \brief This class is used to run JS scripts.
//!        It allows to expose CppModules via V8pp to those
//!        scripts.
//! \tparam Context: V8Context adhering to the ScriptContext concept.
//!        This type will create the v8 context under which the scripts
//!        will be executed.
//! \details This class leverages templates/concepts rather than inhertance
//!        as an abstraction mechanism.
//!
template <ScriptContext Context>
class Runner final
{
public:
    //!
    //! \brief Creates a runner, instantiates V8 via Context::createContext.
    //! \param args: Constructor arguments for the Context type.
    //!
    template<typename ...Args>
    Runner(Args&&...  args) :
        m_context(Context::createContext(std::forward<Args>(args)...))
    {

    }

    //!
    //! \brief Adds modules to context.
    //! \param modules: List of all cpp modules that shall be added
    //!        to the context of the Runner class.
    //!
    template<CppModule ...Modules>
    void loadModules(std::tuple<std::vector<Modules>...>& modules) {
        std::apply([this](auto&... vectors) {
            (..., forEach(vectors));
        },
                   modules);
    }

    //!
    //! \brief Runs a list of provided scripts within the Runner's
    //!        context.
    //! \param scripts: Scripts that are to be executed.
    //!
    template<JSScript ...Scripts>
    void run(std::tuple<std::vector<Scripts>...>& scripts) {
        std::apply([this](auto&... vectors) {
            (..., forEach(vectors));
        },
                   scripts);
        return;
    }

private:
    template <JSScript Script>
    void forEach(std::vector<Script>& vec) {
        for (auto& script : vec) {
            std::cout << "Running script... " << script.name() << std::endl;
            auto result = m_context->context.run_script(script.get());
            script.process(result, m_context->isolate);
            std::cout << std::endl;
        }
    }

    template <CppModule Modules>
    void forEach(std::vector<Modules>& vec) {
        for (auto& module : vec) {
            std::cout << "Loading module..." << module.name() << std::endl;
            v8pp::module v8Module = module.generateModule(m_context->isolate);
            m_context->context.module(module.name(), v8Module);
        }
    }
    std::unique_ptr<Context> m_context {};
};

}
