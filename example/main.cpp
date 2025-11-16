#include <iostream>

#include "v8pp-lab/runner.hpp"
#include "v8pp-lab/scripts.hpp"
#include "v8pp-lab/filelocator.hpp"
#include "coffeemodule/coffemodule.hpp"
#include "v8pp-lab/context.hpp"

int main()
{
    using namespace V8ppLab;
    InMemoryScript memoryScript (R"a("Hello JS " + Coffee.MagicTemperature;)a");
    memoryScript.process = [](v8::Local<v8::Value> result, v8::Isolate* isolate)
    {
        v8::String::Utf8Value utf8(isolate, result);
        std::cout << "Hi Im customized!" << std::endl << *utf8 << std::endl;
    };

    FileLocator locator (DEFAULT_JS_DIR);

    std::tuple<std::vector<InMemoryScript>, std::vector<FileScript>> scripts{
        std::vector{ memoryScript },
        locator.getScripts()
    };

    constexpr CppModule::CoffeeModule coffeeModule {};
    std::tuple<std::vector<CppModule::CoffeeModule>> modules{
        std::vector {coffeeModule}
    };

    Runner<V8Context> runner {};
    std::cout << "-----Loading Modules-----" << std::endl;
    runner.loadModules(modules);

    std::cout << std::endl << "-----Running Scripts-----" << std::endl;
    runner.run(scripts);
    return 0;

}
