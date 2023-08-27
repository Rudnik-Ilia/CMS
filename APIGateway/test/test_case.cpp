#include <iostream>

int main()
{
    int option = 3;

    switch (option)
    {
        case 1:
            std::cout << "Option 1 selected." << std::endl;
        case 2:
            std::cout << "Option 2 selected." << std::endl;
        case 3:
            std::cout << "Option 3 selected." << std::endl;
        case 4:
            std::cout << "Option 4 selected." << std::endl;
        case 5:
            std::cout << "Option 5 selected." << std::endl;
        default:
            std::cout << "Invalid option." << std::endl;
    }

    std::cout << (1 == 2) << std::endl;
    std::cout << (1 == 1) << std::endl;

    return 0;
}