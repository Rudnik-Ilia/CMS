
#include "JSONbuilder.hpp"


JSONbuilder::JSONbuilder(): m_object(json::object())
{
    
}

JSONbuilder::~JSONbuilder()
{

}

JSONbuilder JSONbuilder::AddKeyValue(const std::string key, const std::string value)
{
    m_object[key] = value;
    return *this;
}

std::string JSONbuilder::GetString()
{
    std::string result = m_object.dump();
    return result;
}