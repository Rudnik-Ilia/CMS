#include "../include/master_request.hpp"


MasterRequest::MasterRequest(tcp::socket& socket, http::request<http::string_body>& request): m_socket(socket), m_request(request)
{
    Get_Token();
}

MasterRequest::~MasterRequest()
{
    m_socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
    m_socket.close();
}

void MasterRequest::ForwardTo(const std::string& HOST, const std::string& PORT, const std::string& rest_of_path)
{
    try
    {
        tcp::socket back_end_socket(m_socket.get_executor());
        tcp::endpoint end_point(net::ip::make_address(HOST), std::stoi(PORT));

        back_end_socket.connect(end_point);

        http::write(back_end_socket, m_request);

        beast::flat_buffer buffer;
        http::response<http::string_body> response;
        http::read(back_end_socket, buffer, response);

        http::write(m_socket, response);
    }
    catch(const std::exception& e)
    {
        std::cerr << "Forward request:" << e.what() << '\n';
    }
}

void MasterRequest::ResponseTo(http::status status, const std::string& body)
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

std::string MasterRequest::Get_Token()
{
    auto author = m_request[boost::beast::http::field::authorization];

    if(author.to_string().size() != 0)
    {
        m_token = true;
        return author.to_string();
    }
    else
    {
        m_token = false;
        return std::string("No token");
    }
}
void MasterRequest::RequestTo()
{
    
}

bool MasterRequest::Authorized()
{
    return m_authorized;
}
