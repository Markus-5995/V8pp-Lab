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

//!
//! \brief Default Lambda to process the output of a JS Script ran via v8
//!
static auto defaultProcess = [](v8::Local<v8::Value> result, v8::Isolate* isolate)
{
    v8::String::Utf8Value utf8(isolate, result);
    std::cout << *utf8 << std::endl;
};


class BaseScript
{
public:
    //!
    //! \brief Constructor
    //! \param Identifier for the script. This does not impact the
    //!        execution of the script only how it is displayed in the console
    //!        output.
    //!
    BaseScript(std::string&& name) :
        m_name(std::move(name))
    {

    }

    //!
    //! \brief Identifier for the script. This does not impact the
    //!        execution of the script only how it is displayed in the console
    //!        output.
    //!
    std::string_view name() const
    {
        return m_name;
    }

    //!
    //! \brief Function that is supposed to be called to process the output
    //!        of the JS script.
    //! \details It is intended to assign a different function for customization.
    //!
    ProcessFunction process = defaultProcess;

private:
    std::string m_name;
};


//!
//! \brief This class holds a script direclty in memory.
//!        As a result, no file access is necessary.
//!
class InMemoryScript final : public BaseScript
{
public:
    //!
    //! \brief Constructor
    //! \param script: JS code that is supposed to be executed.
    //!
    explicit InMemoryScript(std::string&& script) noexcept
        : BaseScript("MemoryScript"),
        m_script(std::move(script))
    {

    }

    //!
    //! \brief Constructor
    //! \param script: JS code that is supposed to be executed.
    //! \param name: Identifier for the script. This does not impact the
    //!        execution of the script only how it is displayed in the console
    //!        output.
    //!
    InMemoryScript(std::string&& script, std::string&& name) noexcept
        : BaseScript(std::move(name)),
        m_script(std::move(script))
    {

    }

    //!
    //! \brief Retrieves the content of the script
    //!
    std::string_view get() const
    {
        return m_script;
    }

private:
    std::string m_script {};
    std::string m_name {"In Memory Script"};
};

class FileScript final : public BaseScript
{
public:

    //!
    //! \brief Constructor
    //! \param filepath: Path to the js file
    //!
    FileScript(const std::filesystem::path& filepath) noexcept :
        BaseScript(filepath.filename()),
        m_filepath(filepath)
    {

    }

    //!
    //! \brief Retrieves the content of the script
    //!
    std::string get()
    {
        std::stringstream ss {};
        std::string line {};
        std::ifstream stream (m_filepath);
        while(std::getline(stream, line))
        {
            ss << line << std::endl;
        }
        return ss.str();
    }

private:
    std::filesystem::path m_filepath {};
};

static_assert(JSScript<InMemoryScript>, "Must confrom to 'JSScript' concept!");
static_assert(JSScript<FileScript>, "Must confrom to 'JSScript' concept!");
}
