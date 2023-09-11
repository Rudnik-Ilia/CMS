#include "exeptions.hpp" 


BadAppleExeption::BadAppleExeption(const char * message): m_message(m_message){}

const char* BadAppleExeption::what() const noexcept
{
    return m_message;
}