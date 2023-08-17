#pragma once

#include "../include/irequest.hpp"
#include "../include/SRP_module.hpp"


class Crypto_Request: public IRequest
{
    public:
        explicit Crypto_Request(tcp::socket& socket, http::request<http::string_body>& request, SRP& srp_module);
        Crypto_Request(const Crypto_Request& other);
        Crypto_Request& operator=(const Crypto_Request& other) = delete;
        Crypto_Request(Crypto_Request&& other) = delete;
        Crypto_Request& operator=(Crypto_Request&& other) = delete;
        ~Crypto_Request();

        void RequestTo();
        void ResponseTo(http::status status, const std::string& body);
        void ForwardTo(const std::string& HOST, const std::string& PORT, const std::string& rest_of_path);
    
    private:
        SRP& m_srp;  
        std::string m_token{};
        bool m_authorized;
        tcp::socket& m_socket;
        http::request<http::string_body>& m_request; 
};


Crypto_Request::Crypto_Request(tcp::socket& socket, http::request<http::string_body>& request, SRP& srp_module): m_srp(srp_module), m_authorized(false), m_socket(socket), m_request(request)
{
    json data = nlohmann::json::parse(request.body());
    std::string client_mix = data["mixture"];
    std::string gate_mix = boost::lexical_cast<std::string>(m_srp.get_mixture());

    big_t mix(client_mix);
    m_srp.set_key_for_encode(mix);
    std::string gate_key = boost::lexical_cast<std::string>(m_srp.get_key());

    std::cout << gate_key << std::endl;

    ResponseTo(http::status::ok, gate_mix);
}

Crypto_Request::~Crypto_Request()
{

}

void Crypto_Request::RequestTo()
{

}

void Crypto_Request::ResponseTo(http::status status, const std::string& body)
{
    http::response<http::string_body> response{};
    response.result(status);
    response.version(m_request.version());
    response.set(http::field::server, "Boost.Beast Web Server");
    response.set(http::field::content_type, "text/plain");
    response.body() = body;
    response.prepare_payload();
    http::write(m_socket, response);
}

void Crypto_Request::ForwardTo(const std::string& HOST, const std::string& PORT, const std::string& rest_of_path)
{

}

void ForwardTo(const std::string& HOST, const std::string& PORT, const std::string& rest_of_path)
{

}