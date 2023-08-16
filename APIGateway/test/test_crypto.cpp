#include <iostream>
#include <string>
#include "../include/SRP_module.hpp"
#include <cassert>

int main()
{
    SRP srp;

    std::string original = "Hello, world!";
    std::string key = "216345";

    std::string encrypted = srp.encrypt_by_key(original, key);
    std::string decrypted = srp.encrypt_by_key(encrypted, key);

    std::cout << "Original: " << original << std::endl;
    std::cout << "Encrypted: " << encrypted << std::endl;
    std::cout << "Decrypted: " << decrypted << std::endl;

    assert(original.compare(decrypted) == 0);


    return 0;
}
