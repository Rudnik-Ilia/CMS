#pragma once

#include <map>
#include <functional>
#include <iostream>

#include "server.hpp"

class IRouter
{
    public:
        virtual void HandleSocket(tcp::socket& socket) = 0;
        virtual void AddRoute(const std::string& path, std::function<void(http::request<http::string_body>&, tcp::socket&)> handler) = 0;
};

class Router
{
    public:
        explicit Router();
        Router(const Router& other) = delete;
        Router& operator=(const Router& other) = delete;
        Router(Router&& other) = delete;
        Router& operator=(Router&& other) = delete;
        ~Router();

        void HandleSocket(tcp::socket& socket);
        void AddRoute(const std::string& path, std::function<void(http::request<http::string_body>&, tcp::socket&)> handler);

    private:
        std::map<std::string, std::function<void(http::request<http::string_body>&, tcp::socket&)>> m_routes{};
};
