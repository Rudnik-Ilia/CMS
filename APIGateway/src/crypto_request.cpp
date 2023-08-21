#include "../include/crypto_request.hpp"



Crypto_Request::Crypto_Request(tcp::socket& socket, http::request<http::string_body>& request, SRP& srp_module): m_srp(srp_module), m_socket(socket), m_request(request)
{

}

Crypto_Request::~Crypto_Request()
{

}

void Crypto_Request::Process_Authorizing()
{
        json data = nlohmann::json::parse(m_request.body());
        m_client_mix = data["mixture"];

        std::string gate_mix = boost::lexical_cast<std::string>(m_srp.get_mixture());

        big_t mix(m_client_mix);
        m_srp.set_key_for_encode(mix);
        std::string gate_key = boost::lexical_cast<std::string>(m_srp.get_key());

        std::cout << gate_key << std::endl;
        
        ResponseTo(http::status::ok, gate_mix);
}

void Crypto_Request::RequestTo(const std::string& HOST, const std::string& PORT, const std::string& rest_of_path)
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

std::string Crypto_Request::GetClientMix()
{
    return m_client_mix;
}