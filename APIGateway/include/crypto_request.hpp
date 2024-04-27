#pragma once

#include "../include/SRP_module.hpp"
#include "JSONbuilder.hpp"


class Crypto_Request
{
    public:
        explicit Crypto_Request(tcp::socket& socket, http::request<http::string_body>& request, SRP& srp_module);
        Crypto_Request(const Crypto_Request& other);
        Crypto_Request& operator=(const Crypto_Request& other) = delete;
        Crypto_Request(Crypto_Request&& other) = delete;
        Crypto_Request& operator=(Crypto_Request&& other) = delete;
        ~Crypto_Request();

        // void RequestTo(const std::string& HOST, const std::string& PORT, const std::string& rest_of_path, const std::string body);
        void ResponseBack(http::status status, const std::string& body);
        void ForwardTo(const std::string& HOST, const std::string& PORT, const std::string body);

        void Process_Mix_Exchange();
        void Process_JWT_Obtaing(const std::string key);

        std::string GetClientMix();
    private:
        SRP& m_srp;  
        tcp::socket& m_socket;
        http::request<http::string_body>& m_request;
        std::string m_client_mix{}; 
        json m_data;
        JSONbuilder m_jsonBuilder;

        // for getting JWT request to singin
        std::string m_role{};
        std::string m_login{};
        std::string m_password{};
};

