#pragma once

#include "../include/helper_functions.hpp"

class BaseRequest
{
    public:
        explicit BaseRequest(tcp::socket& socket, http::request<http::string_body>& request);
        BaseRequest(const BaseRequest& other);
        BaseRequest& operator=(const BaseRequest& other) = delete;
        BaseRequest(BaseRequest&& other) = delete;
        BaseRequest& operator=(BaseRequest&& other) = delete;
        virtual ~BaseRequest();

        void ResponseBack(http::status status, const std::string& body);
        void ForwardTo(const std::string& HOST, const std::string& PORT, const std::string& body);

    private:
        tcp::socket& m_socket;
        http::request<http::string_body>& m_request;
};  

BaseRequest::BaseRequest(tcp::socket& socket, http::request<http::string_body>& request): m_socket(socket), m_request(request)
{

}

BaseRequest::~BaseRequest()
{
    m_socket.close();
}

void BaseRequest::ResponseBack(http::status status, const std::string& body)
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

void BaseRequest::ForwardTo(const std::string& HOST, const std::string& PORT, const std::string& body)
{

}

