#pragma once

#include "../include/server.hpp"

class IRequest
{
    public:
        virtual void RequestTo() = 0;
        virtual void ResponseTo(http::status status, const std::string& body) = 0;
        virtual void ForwardTo(const std::string& HOST, const std::string& PORT, const std::string& rest_of_path) = 0;
};