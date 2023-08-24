#pragma once



#include <string>
#include <iostream>

class Drafter
{
    public:
        Drafter(u_int8_t a_set = 0);
        ~Drafter();
        
        // SETTERS***************

        inline Drafter& GET()
        {
            m_setting |= 1;
            return *this;
        } 
        inline Drafter& POST()
        {
            m_setting |= (1 << 1);
            return *this;
        } 
        inline Drafter& PUT()
        {
            m_setting |= (1 << 2);
            return *this;
        } 

        inline Drafter& DELETE()
        {
            m_setting |= (1 << 3);
            return *this;
        } 

        inline Drafter& HAS_BODY()
        {
            m_setting |= (1 << 7);
            return *this;
        } 

// TEMPORALY FOR TEST ***********************************************8
        std::string PrintSet(); 

        u_int8_t PrintSetAsDigit();

        inline void SetOff()
        {
            m_setting &= 0;
        }

    private:
        u_int8_t m_setting;
};



