#include "jsprovider/filelocator.hpp"
#include <ranges>
#include <algorithm>
namespace JSProvider
{

FileLocator::FileLocator(std::string_view jsDirectory) :
    m_directoryIt(jsDirectory) {

}

std::vector<FileScript> FileLocator::getScripts() const {
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

} // namespace JSProvider
