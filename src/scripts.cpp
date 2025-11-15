#include "v8pp-lab/scripts.hpp"
#include <fstream>
#include <sstream>

namespace V8ppLab
{

FileScript::FileScript(const std::string &filepath) noexcept :
    m_filepath(filepath)
{

}

std::string FileScript::get()
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

std::string FileScript::name() const
{
    return m_filepath.filename();
}


}
