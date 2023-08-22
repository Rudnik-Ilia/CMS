#pragma once

#include "key_storage.hpp"
#include "router.hpp"
#include "server.hpp"

#define ROUTE(path, fn) Routing(path, [&APP](http::request<http::string_body>& request, tcp::socket& socket)fn)

class BigBoo
{
    public:
        BigBoo(std::string ip_addr = "0.0.0.0", int port = 9090);
        BigBoo(const BigBoo& other) = delete;
        BigBoo& operator=(const BigBoo& other) = delete;
        BigBoo(BigBoo&& other) = delete;
        BigBoo& operator=(BigBoo& other) = delete;
        ~BigBoo();

        void Routing(const std::string& path, std::function<void(http::request<http::string_body>&, tcp::socket&)> handler);

        void Run();

        void AddMix(std::string clientMix, std::string secretKey);
        std::string GetKey(std::string clientMix);

        void PrintStorage();
   
        
    private:
        net::io_context m_ioContext{};
        tcp::acceptor m_acceptor;
        Router m_router;
        KeyStorage m_keyStorage;  
};

