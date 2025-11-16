#pragma once
#include <filesystem>
#include <vector>
#include <ranges>
#include <algorithm>
#include "scripts.hpp"
namespace V8ppLab
{

//!
//! \brief This class allows to locate all js files within
//!        a specified directory.
//!
class FileLocator final
{
public:
    //!
    //! \brief Constructor
    //! \param jsDirectory: Directory that is to be searched
    //!        for js files.
    //!
    explicit FileLocator(std::string_view jsDirectory) :
        m_directoryIt(jsDirectory)
    {

    }

    //!
    //! \brief Generates FileScript instances based on the content of the
    //!        directory.
    //!
    std::vector<FileScript> getScripts() const
    {
        std::vector<FileScript> vector {};
        auto view = std::ranges::filter_view(m_directoryIt,
                                             [](const std::filesystem::directory_entry& path){
                                                 if (! path.is_regular_file()){
                                                     return false;
                                                 }
                                                 return path.path().extension() == ".js";
                                             });
        std::for_each(view.begin(), view.end(),
                      [&](const auto& path){
                          vector.emplace_back(FileScript(path.path()));
                      });
        return vector;
    }
private:
    std::filesystem::directory_iterator m_directoryIt {};
};

}
