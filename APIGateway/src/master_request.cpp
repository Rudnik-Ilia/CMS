#include "../include/master_request.hpp"


MasterRequest::MasterRequest(tcp::socket& socket, http::request<http::string_body>& request): m_token("No token"), m_authorized(false), m_socket(socket), m_request(request)
{
    if(m_authorized != true)
    {
        Get_Token();
    }
}

MasterRequest::~MasterRequest()
{
    m_socket.close();
}

void MasterRequest::ForwardTo(const std::string& HOST, const std::string& PORT, const std::string& body)
{
    if(m_authorized)
    {
        try
        {   
            tcp::socket back_end_socket(m_socket.get_executor());
            tcp::resolver resolver(back_end_socket.get_executor());

            auto const results = resolver.resolve(HOST, PORT);
            net::connect(back_end_socket, results);

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
    else
    {
        ResponseBack(http::status::unauthorized, "You need to have a token!");
    }
}

void MasterRequest::ResponseBack(http::status status, const std::string& body)
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


void MasterRequest::Get_Token()
{
    auto author = m_request[boost::beast::http::field::authorization];

    if(author.to_string().size() != 0)
    {
        if(Check_Token(author.to_string()) == 1)
        {
            m_token = author.to_string();
            m_authorized = true;
        }
    }
}

int MasterRequest::Check_Token(std::string token)
{
    
}

bool MasterRequest::Authorized()
{
    return m_authorized;
}
// int MasterRequest::Check_Token(std::string token)
// {
//     int code = 0;
    
//     net::io_context ioContext;
//     tcp::socket socket(ioContext);

//     tcp::endpoint end_point(net::ip::make_address("127.0.0.1"), std::stoi("8090"));
//     socket.connect(end_point);

//     http::request<http::string_body> request(http::verb::post, "/check", 11);

//     request.set(http::field::content_type, "application/json"); 
//     request.set(http::field::user_agent, "Boost.Beast");

//     const std::string requestBody = R"({"token": ")" + token + R"("})";
//     request.body() = requestBody;

//     request.prepare_payload();
//     http::write(socket, request);

//     beast::flat_buffer buffer;
//     http::response<http::string_body> response;
//     http::read(socket, buffer, response);

//     if(response.result() == http::status::ok)
//     {
//         code = 1;
//     }

//     socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
//     socket.close();

//     return code;
// }

// void MasterRequest::RequestTo(const std::string& HOST, const std::string& PORT, const std::string& rest_of_path)
// {
//     // tcp::endpoint end_point(net::ip::make_address(HOST), std::stoi(PORT));
//     // m_socket.connect(end_point);

//     // http::request<http::string_body> request(http::verb::post, "/check", 11);
//     // request.set(http::field::content_type, "application/json"); 
//     // request.set(http::field::host, HOST + ":" + PORT);
//     // request.set(http::field::user_agent, "Boost.Beast");

//     // const std::string requestBody = R"({"token": ")" + m_token + R"("})";
//     // request.body() = requestBody;

//     // request.prepare_payload();
//     // http::write(socket, request);

//     // beast::flat_buffer buffer;
//     // http::response<http::string_body> response;
//     // http::read(socket, buffer, response);

//     // std::cout << response.body() << std::endl;
// }