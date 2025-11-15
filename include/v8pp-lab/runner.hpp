#pragma once
#include "appconcepts/script.hpp"
#include "appconcepts/cppmodule.hpp"
#include <vector>
#include <tuple>
#include <iostream>
namespace Runner
{
template <AppConcepts::ScriptEnvironment Environment>
class Runner
{
public:
    template<typename ...Args>
    Runner(Args&&...  args) :
        m_environment(std::forward<Args>(args)...)
    {

    }

    template<AppConcepts::CppModule ...Modules>
    void loadModules(std::tuple<std::vector<Modules>...>&& modules) {
        std::apply([this](auto&... vectors) {
            (..., forEach(vectors));
        },
                   modules);
    }

    template<AppConcepts::JSScript ...Scripts>
    int run(std::tuple<std::vector<Scripts>...> scripts) {
        std::apply([this](auto&... vectors) {
            (..., forEach(vectors));
        },
                   scripts);
        return 0;
    }

private:
    template <AppConcepts::JSScript Script>
    void forEach(std::vector<Script>& vec) {
        for (auto& s : vec) {
            std::cout << "Running script... " << s.name() << std::endl;
            m_environment.runScript(s.get());
        }
    }

    template <AppConcepts::CppModule Modules>
    void forEach(std::vector<Modules>& vec) {
        for (auto& s : vec) {
            std::cout << "Loading module..." << s.name() << std::endl;
            m_environment.addModule(s.name(), s.generateModule(m_environment.getContext()));
        }
    }
    Environment m_environment {};
};

} // namespace Runner
