#pragma once

#include <string>
#include <iostream>

class Drafter
{
    public:
        Drafter(u_int8_t bit_set = 0);
        ~Drafter();
        
        // SETTERS***************

        inline Drafter& GET()
        {
            m_bit_set |= 1;
            return *this;
        } 
        inline Drafter& POST()
        {
            m_bit_set |= (1 << 1);
            return *this;
        } 
        inline Drafter& PUT()
        {
            m_bit_set |= (1 << 2);
            return *this;
        } 

        inline Drafter& DELETE()
        {
            m_bit_set |= (1 << 3);
            return *this;
        } 

        inline Drafter& HAS_BODY()
        {
            m_bit_set |= (1 << 7);
            return *this;
        } 

// TEMPORALY FOR TEST ***********************************************8
        std::string PrintSet(); 

        u_int8_t dot();

        inline void SetOff()
        {
            m_bit_set &= 0;
        }

    private:
        u_int8_t m_bit_set;
};



