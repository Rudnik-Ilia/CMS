#include "crypto_request.hpp"
#include "logger.hpp"


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
        ForwardTo("127.0.0.1", "8090",res);
        CONSOLE_LOG("Decrypted data: " + res);
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
        tcp::endpoint end_point(net::ip::make_address(HOST), std::stoi(PORT));

        back_end_socket.connect(end_point);

        http::write(back_end_socket, m_request);

        beast::flat_buffer buffer;
        http::response<http::string_body> response;
        http::read(back_end_socket, buffer, response);

        http::write(m_socket, response);
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

// void Crypto_Request::RequestTo(const std::string& HOST, const std::string& PORT, const std::string& rest_of_path, const std::string body)
// {
//     tcp::endpoint end_point(net::ip::make_address(HOST), std::stoi(PORT));
//     m_socket.connect(end_point);

//     http::request<http::string_body> request;
//     request.method(http::verb::post);
//     request.target(rest_of_path);
//     request.version(11);
//     request.set(http::field::content_type, "application/json"); 
//     request.set(http::field::host, HOST + ":" + PORT);
//     request.set(http::field::user_agent, "Boost.Beast");
//     request.body() = body;
//     request.prepare_payload();
//     http::write(m_socket, request);

//     // beast::flat_buffer buffer;
//     // http::response<http::string_body> response;
//     // http::read(socket, buffer, response);

//     // std::cout << response.body() << std::endl;
// }