#pragma once
#include "appconcepts/script.hpp"
#include <filesystem>
#include <fstream>
#include <sstream>
namespace JSProvider
{

class InMemoryScript
{
public:
    explicit constexpr InMemoryScript(std::string_view script) noexcept
        : m_script(script)
    {

    }

    constexpr InMemoryScript(std::string_view script, std::string_view name) noexcept
        : m_script(script),
        m_name(name)
    {

    }
    constexpr std::string_view get() const
    {
        return m_script;
    }
    constexpr std::string_view name() const
    {
        return m_name;
    }
private:
    std::string_view m_script {};
    std::string_view m_name {"In Memory Script"};
};

class FileScript
{
public:
    FileScript(const std::string& filepath) noexcept;

    std::string get();

    std::string name() const;
    std::filesystem::path m_filepath {};
};

static_assert(AppConcepts::JSScript<InMemoryScript>, "Must confrom to 'JSScript' concept!");
static_assert(AppConcepts::JSScript<FileScript>, "Must confrom to 'JSScript' concept!");


} // namespace JSProvider
