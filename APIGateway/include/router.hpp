#pragma once

#include <map>
#include <functional>
#include <iostream>

#include "server.hpp"

class IRouter
{
    public:
        virtual void Run(tcp::socket& socket) = 0;
        virtual void AddRoute(const std::string& path, std::function<void(http::request<http::string_body>&, tcp::socket&)> handler) = 0;
};

class Router: public IRouter
{
    public:
        explicit Router();
        Router(const Router& other) = delete;
        Router& operator=(const Router& other) = delete;
        Router(Router&& other) = delete;
        Router& operator=(Router&& other) = delete;
        ~Router();

        void Run(tcp::socket& socket) override;
        void AddRoute(const std::string& path, std::function<void(http::request<http::string_body>&, tcp::socket&)> handler) override;

    private:
        std::map<std::string, std::function<void(http::request<http::string_body>&, tcp::socket&)>> m_routes{};
};
