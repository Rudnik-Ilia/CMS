#include <iostream>
#include "../include/SRP_module.hpp"

// g++ test/test_srp.cpp src/SRP_module.cpp -lm -lpthread -I include

int main()
{
    std::string password = {"My name Ilia!"};

    SRP s1;

    big_t S1mix = s1.get_mixture();
    big_t S1secret = s1.get_secret();


    std::cout << "mix 1: " << S1mix << std::endl;
    std::cout << "secret 1: " << S1secret << std::endl;

    big_t other_mix{};
    std::cin >> other_mix;
    s1.set_key_for_encode(other_mix);
    std::cout << s1.get_key() << std::endl;


    return 0;
}