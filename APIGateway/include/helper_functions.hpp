#pragma once

#include <iostream>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/connect.hpp>
#include <nlohmann/json.hpp>
#include <thread>
#include <cmath>
#include <stdlib.h>

#define DEBUGLINE printf("\n%s:%d\n", __FILE__, __LINE__)
#define LOGINFO(data) std::cout << data << std::endl

static const char start[] = "\x1b[1;31m--------------- BIG_BO START ---------------\x1b[0m\n";
static const char end[] =   "\x1b[1;31m--------------- BIG_BO STOP -----------------\x1b[0m\n";

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;


using json = nlohmann::json;
using tcp = net::ip::tcp;

enum REQUEST_TYPE
{
    GET = 0,
    POST, 
    PUT,
    DELETE,
    UNSUPPORTED
};

int TypeRequest(tcp::socket& socket, http::request<http::string_body>& request);

void Send_Response(tcp::socket& socket, http::request<http::string_body>& request, http::status status, const std::string& body);

void Forward_Request(tcp::socket &socket, http::request<http::string_body> &request, const std::string &host_name, const std::string &PORT, const std::string &rest_of_path);


