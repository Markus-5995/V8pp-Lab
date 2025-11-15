#pragma once
#include <filesystem>
#include <functional>
#include <iostream>
#include <fstream>
#include <sstream>
#include "v8pp-lab/concepts.hpp"

namespace V8ppLab
{

using ProcessFunction = std::function<void(v8::Local<v8::Value> result, v8::Isolate* isolate)>;

static auto defaultProcess = [](v8::Local<v8::Value> result, v8::Isolate* isolate)
{
    v8::String::Utf8Value utf8(isolate, result);
    std::cout << *utf8 << std::endl;
};


class InMemoryScript final
{
public:
    explicit InMemoryScript(std::string_view script) noexcept
        : m_script(std::string(script))
    {

    }

    InMemoryScript(std::string_view script, std::string_view name) noexcept
        : m_script(std::string(script)),
        m_name(std::string(name))
    {

    }
    std::string_view get() const
    {
        return m_script;
    }
    std::string_view name() const
    {
        return m_name;
    }

    ProcessFunction process = defaultProcess;
private:
    std::string m_script {};
    std::string m_name {"In Memory Script"};
};

class FileScript final
{
public:
    FileScript(const std::string& filepath) noexcept :
        m_filepath(filepath)
    {

    }

    std::string get()
    {
        std::stringstream ss {};
        std::string line {};
        std::ifstream stream (m_filepath);
        while(std::getline(stream, line))
        {
            ss << line;
        }
        return ss.str();
    }

    std::string name() const
    {
        return m_filepath.filename();
    }
    std::filesystem::path m_filepath {};

    ProcessFunction process = defaultProcess;
};

static_assert(JSScript<InMemoryScript>, "Must confrom to 'JSScript' concept!");
static_assert(JSScript<FileScript>, "Must confrom to 'JSScript' concept!");
}
