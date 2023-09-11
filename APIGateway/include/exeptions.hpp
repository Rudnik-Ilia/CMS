#pragma once

#include <stdexcept>

class BadAppleExeption: public std::exception
{
    public:
        BadAppleExeption(const char * message);
        BadAppleExeption(const BadAppleExeption& other) = default;
        ~BadAppleExeption() = default;
        const char* what() const noexcept override;

    private:
        const char * m_message;
};

