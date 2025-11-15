#pragma once
#include <filesystem>
#include <vector>
#include "scripts.hpp"
namespace JSProvider
{

class FileLocator
{
public:
    FileLocator(std::string_view jsDirectory);
    std::vector<FileScript> getScripts() const;
private:
    std::filesystem::directory_iterator m_directoryIt {};
};

} // namespace JSProvider
