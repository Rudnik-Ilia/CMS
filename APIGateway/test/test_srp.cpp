#include <iostream>
#include "../include/header.hpp"

// g++ test/test_srp.cpp -lm -lpthread

int main()
{
    SRP s(2, 34);
    SRP s1(2, 22);

    std::cout << s.get_key_for_encode(s1.get_mixture()) << std::endl;
    std::cout << s1.get_key_for_encode(s.get_mixture()) << std::endl;



    


    return 0;
}