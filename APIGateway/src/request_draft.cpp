#include "../include/request_draft.hpp"

Drafter::Drafter(u_int8_t a_set): m_setting(a_set){}

Drafter::~Drafter(){}


std::string Drafter::PrintSet()
{
    std::string result;
    for (int i = 7; i >= 0; --i) 
    {
        result += std::to_string((m_setting >> i) & 1);
    }
    return result;
}
u_int8_t Drafter::PrintSetAsDigit()
{
    return m_setting;
}
