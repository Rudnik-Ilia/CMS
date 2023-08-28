#include "../include/drafter.hpp"

Drafter::Drafter(u_int8_t bit_set){}

Drafter::~Drafter(){}

std::string Drafter::PrintSet()
{
    std::string result;
    for (int i = 7; i >= 0; --i) 
    {
        result += std::to_string((m_bit_set >> i) & 1);
    }
    return result;
}
u_int8_t Drafter::dot()
{
    return m_bit_set;
}
