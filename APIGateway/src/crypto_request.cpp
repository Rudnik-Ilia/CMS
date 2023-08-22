#include "../include/crypto_request.hpp"



Crypto_Request::Crypto_Request(tcp::socket& socket, http::request<http::string_body>& request, SRP& srp_module): m_srp(srp_module), m_socket(socket), m_request(request)
{
    m_data = nlohmann::json::parse(m_request.body());
}

Crypto_Request::~Crypto_Request()
{
    m_socket.close();
}

void Crypto_Request::Process_Mix_Exchange()
{
    if(m_data.contains("mixture"))
    {
        m_client_mix = m_data["mixture"];
        m_srp.set_mixture();
        m_srp.set_key_for_encode(big_t (m_client_mix));
        
        ResponseTo(http::status::ok, m_srp.get_mix_asString());
    }
    else
    {
        std::cerr << "Mix exchange: " << '\n';
        ResponseTo(http::status::bad_request, "Check the message format!");
    }
}

void Crypto_Request::Process_JWT_Obtaing()
{
    
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