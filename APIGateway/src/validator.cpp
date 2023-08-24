#include "validator.hpp"
#include "logger.hpp"


Validator::Validator()
{

}

Validator::~Validator()
{

}

void Validator::Check(tcp::socket& socket, http::request<http::string_body>& request, u_int8_t draft)
{
    
    switch (request.method()) 
    {
        case http::verb::get:
            CONSOLE_LOG("GET request from: " + request.target().to_string());
            break;

        case http::verb::post:
            CONSOLE_LOG("POST request from: " + request.target().to_string());
            break;

        case http::verb::put:
            CONSOLE_LOG("PUT request from: " + request.target().to_string());
            break;

        case http::verb::delete_:
            CONSOLE_LOG("DELETE request from: " + request.target().to_string());
            break;
    
        default:
            CONSOLE_LOG("UNKNOWN PATH " + request.target().to_string());
            Send_Response(socket, request, http::status::not_found, "Unknown path!");
            break;
    }
}

void Validator::IsBody(tcp::socket& socket, http::request<http::string_body>& request)
{
    if(!request.body().empty())
    {
        return;
    }
    else
    {
        CONSOLE_LOG("CHECKING BODY FAIL" + request.target().to_string() + "[ refused ]");
        Send_Response(socket, request, http::status::bad_request, "Check the body!");
        socket.shutdown(tcp::socket::shutdown_both);
        socket.close();
        return;
    }
}