#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <chrono>

namespace mp = boost::multiprecision;

bool is_prime(const mp::cpp_int &num)
{
    if (num <= 1)
        return false;
    for (mp::cpp_int i = 2; i * i <= num; ++i)
    {
        if (num % i == 0)
            return false;
    }
    return true;
}


int main()
{
    // mp::cpp_int num("2");
    // mp::cpp_int exp("2843");
    // mp::cpp_int result = power(num, exp);

    // std::cout << result << std::endl;

    // boost::random::mt19937 rng(std::time(0));

    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    boost::random::mt19937 rng(static_cast<unsigned int>(seed));

    mp::cpp_int min_value = mp::pow(mp::cpp_int(10), 9);
    mp::cpp_int max_value = mp::pow(mp::cpp_int(10), 10) - 1;


    boost::random::uniform_int_distribution<mp::cpp_int> distribution(min_value, max_value);
    mp::cpp_int random_number = distribution(rng);

    std::cout << "Random 10-Digit Big Number: " << random_number << std::endl;
    std::cout << min_value << std::endl;
    std::cout << max_value << std::endl;

    return 0;
}
