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

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;


using json = nlohmann::json;
using tcp = net::ip::tcp;


void Define_type_Request(http::request<http::string_body> &request);

void Send_Response(tcp::socket &socket, http::request<http::string_body> &request, const std::string &body);

void Handle_Connection(tcp::socket socket);

void Forward_Request(tcp::socket &socket, http::request<http::string_body> &request, const std::string &host_name, const std::string &PORT, const std::string &rest_of_path);

