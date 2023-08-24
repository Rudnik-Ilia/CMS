#include <iostream>
#include <cassert>

#include "../include/request_draft.hpp"
#include "../include/validator.hpp"

// g++ test/test_drafter.cpp src/request_drafter.cpp -lpthread

int main()
{
    Drafter drafter;


    std::cout << drafter.PrintSet() << std::endl;

    drafter.GET();
    std::cout << drafter.PrintSet() << std::endl;
    std::cout << drafter.PrintSetAsDigit() << std::endl;
    assert( drafter.PrintSetAsDigit() == TYPE_GET);
    drafter.SetOff();

    drafter.POST();
    std::cout << drafter.PrintSet() << std::endl;
    std::cout << drafter.PrintSetAsDigit() << std::endl;
    assert( drafter.PrintSetAsDigit() == TYPE_POST);
    drafter.SetOff();

    drafter.PUT();
    std::cout << drafter.PrintSet() << std::endl;
    std::cout << drafter.PrintSetAsDigit() << std::endl;
    assert( drafter.PrintSetAsDigit() == TYPE_PUT);
    drafter.SetOff();

    drafter.PUT().HAS_BODY();
    std::cout << drafter.PrintSet() << std::endl;
    std::cout << drafter.PrintSetAsDigit() << std::endl;
    assert( drafter.PrintSetAsDigit() == TYPE_PUT_WITH_BODY);
    drafter.SetOff();

    drafter.DELETE();
    std::cout << drafter.PrintSet() << std::endl;
    std::cout << drafter.PrintSetAsDigit() << std::endl;
    assert(drafter.PrintSetAsDigit() == TYPE_DELETE);
    drafter.SetOff();

    drafter.POST().HAS_BODY();
    std::cout << drafter.PrintSet() << std::endl;
    std::cout << drafter.PrintSetAsDigit() << std::endl;
    assert(drafter.PrintSetAsDigit() == TYPE_POST_WITH_BODY);

    drafter.SetOff();

    std::cout << drafter.PrintSet() << std::endl;
    std::cout << drafter.PrintSetAsDigit() << std::endl;
    assert( drafter.PrintSetAsDigit() == 0);
}