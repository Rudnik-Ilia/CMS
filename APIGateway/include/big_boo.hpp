#pragma once

#include <atomic>
#include <csignal>

#include "key_storage.hpp"
#include "router.hpp"
#include "helper_functions.hpp"
#include "logger.hpp"
#include "credention.hpp"
#include "exeptions.hpp"

#define ROUTE(path, fn) Routing(path, [&APP](http::request<http::string_body>& request, tcp::socket& socket)fn)

const std::string AUTH_SERV_ADDR = "auth-flask-app";
const std::string AUTH_SERV_PORT = "8090";

const std::string MAIL_AGENT_ADDR = "mailagent-flask-app";
const std::string MAIL_AGENT_PORT = "8008";

const std::string DB_MANAGER_ADDR = "dbmanager-flask-app";
const std::string DB_MANAGER_PORT = "8000";

class BigBoo
{
    public:
        BigBoo(std::string ip_addr = "0.0.0.0", int port = 9999);
        BigBoo(const BigBoo& other) = default;
        BigBoo& operator=(const BigBoo& other) = delete;
        BigBoo(BigBoo&& other) = delete;
        BigBoo& operator=(BigBoo& other) = delete;
        ~BigBoo();

        void Routing(const std::string& path, std::function<void(http::request<http::string_body>&, tcp::socket&)> handler);

        void Run();

        void AddMix(std::string clientMix, std::string secretKey);

        std::string GetKey(const std::string clientMix);

// TEMPORALY******
        void PrintStorage();

    private:
        static void StopHandler(int signal);
        static std::atomic<bool> m_stop_flag;

        net::io_context m_ioContext{};
        tcp::acceptor m_acceptor;
        Router m_router;
        KeyStorage m_keyStorage;  
        // Logger m_logger;
};

