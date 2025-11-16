#pragma once
#include "v8pp-lab/concepts.hpp"
#include <vector>
#include <tuple>
#include <iostream>
namespace V8ppLab
{
template <ScriptContext Context>
class Runner final
{
public:
    template<typename ...Args>
    Runner(Args&&...  args) :
        m_context(Context::createContext(std::forward<Args>(args)...))
    {

    }

    template<CppModule ...Modules>
    void loadModules(std::tuple<std::vector<Modules>...>& modules) {
        std::apply([this](auto&... vectors) {
            (..., forEach(vectors));
        },
                   modules);
    }

    template<JSScript ...Scripts>
    int run(std::tuple<std::vector<Scripts>...>& scripts) {
        std::apply([this](auto&... vectors) {
            (..., forEach(vectors));
        },
                   scripts);
        return 0;
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
