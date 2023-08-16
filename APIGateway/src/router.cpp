#include "../include/router.hpp"
#include "../include/server.hpp"

Router::Router()
{

}
Router::~Router()
{

}

void Router::AddRoute(const std::string& path, std::function<void(http::request<http::string_body>&, tcp::socket&)> handler) 
{
    m_routes[path] = std::move(handler);
}

void Router::Run(tcp::socket& socket)
{    
    beast::flat_buffer buffer;
    http::request<http::string_body> request;
    http::read(socket, buffer, request);

    auto it = m_routes.find(request.target().to_string());

    if (it != m_routes.end()) 
    {
        it->second(request, socket);
    } 
    else 
    {
        Send_Response(socket, request, http::status::not_found, "Unknown path!");
    }
}
