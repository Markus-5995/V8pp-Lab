#pragma once
#include <filesystem>
#include <vector>
#include "scripts.hpp"
namespace V8ppLab
{

class FileLocator final
{
public:
    explicit FileLocator(std::string_view jsDirectory);
    std::vector<FileScript> getScripts() const;
private:
    std::filesystem::directory_iterator m_directoryIt {};
};

}
