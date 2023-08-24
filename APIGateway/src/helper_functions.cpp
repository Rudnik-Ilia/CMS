#include "helper_functions.hpp"
#include "SRP_module.hpp"
#include "logger.hpp"

std::string HOST = "127.0.0.1";
std::string PORT = "8000";

std::string host_auth = "127.0.0.1";
std::string port_auth = "8090";

int Validator_Func(tcp::socket& socket, http::request<http::string_body>& request) 
{
    switch (request.method()) 
    {
        case http::verb::get:
            CONSOLE_LOG("GET request from: " + request.target().to_string());
            return GET;

        case http::verb::post:
            if(!request.body().empty())
            {
                CONSOLE_LOG("POST request from: " + request.target().to_string());
                return POST;
            }
            else
            {
                std::cout << "Empty body!" << std::endl;
                Send_Response(socket, request, http::status::bad_request, "Check the body!");
                socket.shutdown(tcp::socket::shutdown_both);
                socket.close();
                return UNSUPPORTED;
            }
        
        case http::verb::put:
            std::cout << "Received a PUT request" << std::endl;
            return PUT;
    
        case http::verb::delete_:
            std::cout << "Received a DELETE request" << std::endl;
            return DELETE;
    
        default:
            std::cout << "Received an unsupported request method" << std::endl;
            Send_Response(socket, request, http::status::not_found, "Unknown path!");
            return UNSUPPORTED;
    }
}

void Send_Request(const std::string& HOST, const std::string& PORT, const std::string& rest_of_path)
{
    net::io_context ioContext;
    tcp::socket socket(ioContext);

    tcp::endpoint end_point(net::ip::make_address(HOST), std::stoi(PORT));
    socket.connect(end_point);

    http::request<http::string_body> request(http::verb::post, "/check", 11);
    request.set(http::field::content_type, "application/json"); 
    request.set(http::field::host, HOST + ":" + port_auth);
    request.set(http::field::user_agent, "Boost.Beast");

    request.prepare_payload();
    http::write(socket, request);

    beast::flat_buffer buffer;
    http::response<http::string_body> response;
    http::read(socket, buffer, response);

    std::cout << response.body() << std::endl;

    socket.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
    socket.close();    
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


