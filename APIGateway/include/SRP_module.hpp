#pragma once

#include <stdbool.h>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include <chrono>

using big_t = boost::multiprecision::cpp_int;

const big_t ROOT = 3;
const big_t PRIME = 166771;

const big_t MIN_VAL = 1000;
const big_t MAX_VAL = 9999;


class SRP
{
    public:
        explicit SRP();
        SRP(const SRP& other) = delete;
        SRP& operator=(const SRP& other) = delete;
        SRP(SRP&& other) = delete;
        SRP& operator=(SRP&& other) = delete;
        ~SRP(){};

        big_t get_mixture() const;
        void set_key_for_encode(big_t mix);

        big_t get_secret() const;
        big_t get_key() const;

        std::string encrypt_by_key(const std::string &plaintext, const std::string &key);
        std::string decrypt_by_key(const std::string &cryptotext, const std::string &key);

    private:
        big_t m_secret;
        big_t m_key;
        std::string m_s_key;

        inline bool is_prime(const big_t &num) const
        {
            if (num <= 1)
                return false;
            for (big_t i = 2; i * i <= num; ++i)
            {
                if (num % i == 0)
                    return false;
            }
            return true;
        }
};


