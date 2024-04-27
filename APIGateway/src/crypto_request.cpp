#include "crypto_request.hpp"
#include "logger.hpp"
#include "big_boo.hpp"


Crypto_Request::Crypto_Request(tcp::socket& socket, http::request<http::string_body>& request, SRP& srp_module): m_srp(srp_module), m_socket(socket), m_request(request), m_jsonBuilder()
{
    m_data = nlohmann::json::parse(m_request.body());
    m_client_mix = m_data["mixture"];
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
        m_srp.set_key_for_encode(big_t(m_client_mix));
        
        ResponseBack(http::status::ok, m_srp.get_mix_asString());
    }
    else
    {
        std::cerr << "Mix exchange: " << '\n';
        ResponseBack(http::status::bad_request, "Check the message format!");
    }
}

void Crypto_Request::Process_JWT_Obtaing(const std::string key)
{
    // m_client_mix = m_data["mixture"];
    if(key != "")
    {
        m_login = SRP::decrypt_by_key(m_data["login"], key);
        m_password = SRP::decrypt_by_key(m_data["password"], key);
        std::string res = m_jsonBuilder.AddKeyValue("login", m_login).AddKeyValue("password", m_password).GetString();

        ForwardTo(AUTH_SERV_ADDR, AUTH_SERV_PORT, res);

        LOGINFO("Decrypted data: " + res);
    }
    else
    {
        ResponseBack(http::status::bad_request, "Your mix was alredy used!");
    }
}

void Crypto_Request::ResponseBack(http::status status, const std::string& body)
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

void Crypto_Request::ForwardTo(const std::string& HOST, const std::string& PORT, const std::string body)
{
    try
    {
        m_request.content_length(body.size());
        m_request.body() = std::move(body);

        tcp::socket back_end_socket(m_socket.get_executor());
        tcp::resolver resolver(back_end_socket.get_executor());

        auto const results = resolver.resolve(HOST, PORT);
        net::connect(back_end_socket, results);

        write(back_end_socket, m_request);

        beast::flat_buffer buffer;
        http::response<http::string_body> response;
        read(back_end_socket, buffer, response);

        write(m_socket, response);
        return;
    }
    catch(const std::exception& e)
    {
        std::cerr << "Forward request:" << e.what() << '\n';
    }
}

std::string Crypto_Request::GetClientMix()
{
    return m_client_mix;
}
