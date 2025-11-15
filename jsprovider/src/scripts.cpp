#include "jsprovider/scripts.hpp"
namespace JSProvider
{

JSProvider::FileScript::FileScript(const std::string &filepath) noexcept :
    m_filepath(filepath)
{

}

std::string JSProvider::FileScript::get()
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

std::string JSProvider::FileScript::name() const
{
    return m_filepath.filename();
}


} // namespace JSProvider
