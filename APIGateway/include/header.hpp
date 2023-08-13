#pragma once

#include <iostream>
#include <string>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/connect.hpp>
#include <nlohmann/json.hpp>
#include <thread>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

using json = nlohmann::json;

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = net::ip::tcp;

void Define_type_Request(http::request<http::string_body> &request);

void Send_Response(tcp::socket &socket, http::request<http::string_body> &request, const std::string &body);

void Handle_Connection(tcp::socket socket);

void Forward_Request(tcp::socket &socket, http::request<http::string_body> &request, const std::string &host_name, const std::string &PORT, const std::string &rest_of_path);

class SRP
{
    public:
        SRP(size_t digits, size_t secret): m_digits(digits), m_simple_prime(2), m_secret(secret)
        {
            srand(time(NULL));
            m_big_prime = generate_prime_with_digits();
            std::cout << m_big_prime << std::endl;

        }
        ~SRP()
        {
        }

        size_t get_mixture()
        {
            size_t result = power(m_simple_prime, m_secret);
            return result % m_big_prime;
            std::cout << result << std::endl;
        }

        size_t get_key_for_encode(size_t mix)
        {
            size_t result = power(mix, m_secret);
            return result % m_big_prime;
        }

    

    private:

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


        size_t generate_prime_with_digits()
        {
            size_t min_value = 1;
            for (size_t i = 1; i < m_digits; ++i)
            {
                min_value *= 10;
            }
            size_t max_value = min_value * 10 - 1;


            size_t prime_candidate = min_value + rand() % (max_value - min_value + 1);
            if (prime_candidate % 2 == 0)
            {
                prime_candidate++;
            }

            while(true)
            {
                if (is_prime(prime_candidate))
                {
                    return prime_candidate;
                }
                prime_candidate += 2;
            }
        }

        size_t power(size_t base, int exponent) 
        {
            size_t result = 1;

            if (exponent < 0) 
            {
                base = 1.0 / base;
                exponent = -exponent;
            }

            for (int i = 0; i < exponent; ++i) 
            {
                result *= base;
            }

            return result;
        }

        size_t m_digits;
        size_t m_secret;
        size_t m_simple_prime;
        size_t m_big_prime;
};
