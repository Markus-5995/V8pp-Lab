#include <iostream>

#include "v8pp-lab/runner.hpp"
#include "v8pp-lab/scripts.hpp"
#include "v8pp-lab/filelocator.hpp"
#include "coffeemodule/coffemodule.hpp"
#include "v8pp-lab/environment.hpp"

int main(int argc, char* argv[])
{
    using namespace V8ppLab;
    InMemoryScript memoryScript (R"a("Hello JS " + Coffee.MagicTemperature;)a");
    memoryScript.process = [](v8::Local<v8::Value> result, v8::Isolate* isolate)
    {
        v8::String::Utf8Value utf8(isolate, result);
        std::cout << "Hi Im customized!" << std::endl << *utf8 << std::endl;
    };

    std::vector<FileScript> fileBasedScripts {};
    if (argc == 2)
    {
        FileLocator locator (argv[1]);
        fileBasedScripts = locator.getScripts();
    }
    else
    {
        FileLocator locator (DEFAULT_JS_DIR);
        fileBasedScripts = locator.getScripts();
    }

    std::tuple<std::vector<InMemoryScript>, std::vector<FileScript>> scripts{
        std::vector{ memoryScript },
        fileBasedScripts
    };

    constexpr CppModule::CoffeeModule coffeeModule {};
    std::tuple<std::vector<CppModule::CoffeeModule>> modules{
        std::vector {coffeeModule}
    };

    Runner<V8ppEnvironment> runner {};
    std::cout << "-----Loading Modules-----" << std::endl;
    runner.loadModules(std::move(modules));

    std::cout << "-----Running Scripts-----" << std::endl;
    return runner.run(std::move(scripts));
}
