#include "runner/runner.hpp"
#include "jsprovider/scripts.hpp"
#include "jsprovider/filelocator.hpp"
#include "coffeemodule/coffemodule.hpp"
#include "runner/../../src/v8ppenvironment.hpp"
#include <iostream>


int main(int argc, char* argv[])
{
    constexpr JSProvider::InMemoryScript memoryScript (R"a("Hello JS " + Coffee.MagicTemperature;)a");

    std::vector<JSProvider::FileScript> fileBasedScripts {};
    if (argc == 2)
    {
        JSProvider::FileLocator locator (argv[1]);
        fileBasedScripts = locator.getScripts();
    }

    std::tuple<std::vector<JSProvider::InMemoryScript>, std::vector<JSProvider::FileScript>> scripts{
        std::vector{ memoryScript },
        fileBasedScripts
    };

    constexpr CppModule::CoffeeModule coffeeModule {};
    std::tuple<std::vector<CppModule::CoffeeModule>> modules{
        std::vector {coffeeModule}
    };

    Runner::Runner<Runner::V8ppEnvironment> runner {};
    runner.loadModules(std::move(modules));

    std::cout << "----------------" << std::endl;
    return runner.run(std::move(scripts));
}
