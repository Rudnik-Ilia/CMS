#pragma once

#include "helper_functions.hpp"

class JSONbuilder
{
        
    public:
        JSONbuilder();
        ~JSONbuilder();

        JSONbuilder AddKeyValue(const std::string key, const std::string value);
        std::string GetString();
    private:
        json m_object;
};




