#include "server.hpp"
#include "SRP_module.hpp"

std::string HOST = "127.0.0.1";
std::string PORT = "8000";

std::string host_auth = "127.0.0.1";
std::string port_auth = "8090";

void Define_type_Request(http::request<http::string_body>& request) 
{
    switch (request.method()) 
    {
        case http::verb::get:
            std::cout << "Received a GET request" << std::endl;
            break;
        case http::verb::post:
            std::cout << "Received a POST request" << std::endl;
            break;
        case http::verb::put:
            std::cout << "Received a PUT request" << std::endl;
            break;
        case http::verb::delete_:
            std::cout << "Received a DELETE request" << std::endl;
            break;
        default:
            std::cout << "Received an unsupported request method" << std::endl;
            break;
    }
}

void Send_Response(tcp::socket& socket, http::request<http::string_body>& request, http::status status, const std::string& body)
{
    http::response<http::string_body> response{};

    response.result(status);
    response.version(request.version());
    response.set(http::field::server, "Boost.Beast Web Server");
    response.set(http::field::content_type, "text/plain");
    response.body() = body;

    response.prepare_payload();
    http::write(socket, response);    
}

std::string Get_Token(http::request<http::string_body>& request)
{
    auto author = request[boost::beast::http::field::authorization];

    if(author.to_string().size() != 0)
    {

        return author.to_string();
    }
    else
    {
        return std::string("No token");
    }
}

int Check_Token(std::string token)
{
    net::io_context ioContext;
    tcp::socket socket(ioContext);

    tcp::endpoint end_point(net::ip::make_address(HOST), std::stoi(port_auth));
    socket.connect(end_point);

    http::request<http::string_body> request(http::verb::post, "/check", 11);
    request.set(http::field::content_type, "application/json"); 
    request.set(http::field::host, HOST + ":" + port_auth);
    request.set(http::field::user_agent, "Boost.Beast");

    const std::string requestBody = R"({"token": ")" + token + R"("})";
    request.body() = requestBody;

    request.prepare_payload();
    http::write(socket, request);


    beast::flat_buffer buffer;
    http::response<http::string_body> response;
    http::read(socket, buffer, response);

    std::cout << response.body() << std::endl;

    socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
    socket.close();

    return 1;
}

void Handle_Connection(tcp::socket socket)
{
    try
    {
        beast::flat_buffer buffer;
        http::request<http::string_body> request;
        http::read(socket, buffer, request);
        if(request.target() == "/mix" && request.method() == http::verb::post)
        {
            json data = nlohmann::json::parse(request.body());
            std::string client_mix = data["mixture"];

            SRP srp;
            std::string gate_mix = boost::lexical_cast<std::string>(srp.get_mixture());

            big_t mix(client_mix);
            srp.set_key_for_encode(mix);
            std::string gate_key = boost::lexical_cast<std::string>(srp.get_key());

            std::cout << gate_key << std::endl;
      
            Send_Response(socket, request, http::status::ok, gate_mix);

            return;
        }
        else if(request.target() == "/signin" && request.method() == http::verb::post)
        {
            Forward_Request(socket, request, host_auth, port_auth, "rest");
        }
        else
        {
            auto token = Get_Token(request);

            if(token.compare("No token") == 0)
            {
                Send_Response(socket, request, http::status::unauthorized, "You need to have a token!");
            }
            else
            {   
                if(Check_Token(token))
                {
                    // Forward_Request(socket, request, HOST, PORT, "rest");
                }
                else
                {
                    Send_Response(socket, request, http::status::unauthorized, "You need to have a VALID token!");
                }
            }
        }
        socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
        socket.close();
    }
    catch(const std::exception& e)
    {
        std::cerr << "Handle_Connection " << e.what() << '\n';
    }
}

void Forward_Request(tcp::socket& socket, http::request<http::string_body>& request, const std::string& HOST, const std::string& PORT, const std::string& rest_of_path)
{
    try
    {
        tcp::socket back_end_socket(socket.get_executor());
        tcp::endpoint end_point(net::ip::make_address(HOST), std::stoi(PORT));

        back_end_socket.connect(end_point);

        http::write(back_end_socket, request);

        beast::flat_buffer buffer;
        http::response<http::string_body> response;
        http::read(back_end_socket, buffer, response);

        http::write(socket, response);
    }
    catch(const std::exception& e)
    {
        std::cerr << "Forward request:" << e.what() << '\n';
    }
}

void Request_to_AuthorizationService()
{

}

void Define_Service(http::request<http::string_body>& request)
{

}

