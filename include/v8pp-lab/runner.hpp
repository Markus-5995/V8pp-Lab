#pragma once
#include "v8pp-lab/concepts.hpp"
#include <vector>
#include <tuple>
#include <iostream>
namespace V8ppLab
{
template <ScriptEnvironment Environment>
class Runner final
{
public:
    template<typename ...Args>
    Runner(Args&&...  args) :
        m_environment(std::forward<Args>(args)...)
    {

    }

    template<CppModule ...Modules>
    void loadModules(std::tuple<std::vector<Modules>...>&& modules) {
        std::apply([this](auto&... vectors) {
            (..., forEach(vectors));
        },
                   modules);
    }

    template<JSScript ...Scripts>
    int run(std::tuple<std::vector<Scripts>...> scripts) {
        std::apply([this](auto&... vectors) {
            (..., forEach(vectors));
        },
                   scripts);
        return 0;
    }

private:
    template <JSScript Script>
    void forEach(std::vector<Script>& vec) {
        for (auto& s : vec) {
            std::cout << "Running script... " << s.name() << std::endl;
            m_environment.runScript(s);
        }
    }

    template <CppModule Modules>
    void forEach(std::vector<Modules>& vec) {
        for (auto& s : vec) {
            std::cout << "Loading module..." << s.name() << std::endl;
            m_environment.addModule(s);
        }
    }
    Environment m_environment {};
};

}
