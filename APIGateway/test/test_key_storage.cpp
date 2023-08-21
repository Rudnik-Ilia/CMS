#include <iostream>

#include "key_storage.hpp"

int main()
{
    KeyStorage storage;

    storage.AddKey("2345", "45678");
    storage.AddKey("cewcew", "45xqwcxwq8");
    storage.AddKey("00987", "4xxq");
    storage.AddKey("2345comvcoie", "45cwcnoi678");

    storage.RemoveKey("2345");
    storage.RemoveKey("cewcew");


    for(const auto &item : storage)
    {
        std::cout << item.first << ' ' << item.second << std::endl;
    }

    std::cout << storage.GetKey("00987") << std::endl;

    return 0;
}