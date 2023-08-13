#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

bool is_prime(size_t num)
{
    if (num <= 1)
    {
        return false;
    }
    for (size_t i = 2; i * i <= num; ++i)
    {
        if (num % i == 0)
        {
            return false;
        }
    }
    return true;
}


size_t generate_prime_with_digits(size_t digits)
{
    size_t min_value = 1;
    for (size_t i = 1; i < digits; ++i)
    {
        min_value *= 10;
    }
    size_t max_value = min_value * 10 - 1;


    size_t prime_candidate = min_value + rand() % (max_value - min_value + 1);
    if (prime_candidate % 2 == 0)
    {
        prime_candidate++;
    }

    while (true)
    {
        if (is_prime(prime_candidate))
        {
            return prime_candidate;
        }
        prime_candidate += 2;
    }
}

int main()
{
    srand(time(NULL));

    size_t digits = 10; // Number of digits in the prime number
    size_t prime = generate_prime_with_digits(2);

    printf("Prime number with %zu digits: %zu\n", digits, prime);

    return 0;
}
