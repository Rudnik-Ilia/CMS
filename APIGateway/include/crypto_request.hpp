#pragma once

#include "../include/irequest.hpp"
#include "../include/SRP_module.hpp"


class Crypto_Request
{
    public:
        explicit Crypto_Request(tcp::socket& socket, http::request<http::string_body>& request, SRP& srp_module);
        Crypto_Request(const Crypto_Request& other);
        Crypto_Request& operator=(const Crypto_Request& other) = delete;
        Crypto_Request(Crypto_Request&& other) = delete;
        Crypto_Request& operator=(Crypto_Request&& other) = delete;
        ~Crypto_Request();

        void RequestTo(const std::string& HOST, const std::string& PORT, const std::string& rest_of_path);
        void ResponseTo(http::status status, const std::string& body);
        void ForwardTo(const std::string& HOST, const std::string& PORT, const std::string& rest_of_path);

        void Process_Authorizing();
 
    
    private:
        SRP& m_srp;  
        tcp::socket& m_socket;
        http::request<http::string_body>& m_request; 
};

