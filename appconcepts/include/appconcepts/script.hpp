#pragma once
#include <string_view>
#include <concepts>

namespace AppConcepts
{
template<typename T>
concept JSScript = requires(T t)
{
    {t.get()} -> std::convertible_to<std::string_view>;
    {t.name()} -> std::convertible_to<std::string_view>;
};

}
