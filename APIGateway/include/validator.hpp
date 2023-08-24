#pragma once

#include "../include/helper_functions.hpp"

enum SET_REQUEST
{
    TYPE_GET = 1,
    TYPE_POST = 2,
    TYPE_PUT = 4,
    TYPE_DELETE = 8,
    TYPE_GET_WITH_BODY = 129,
    TYPE_POST_WITH_BODY = 130,
    TYPE_PUT_WITH_BODY  = 132,
    TYPE_DELETE_WITH_BODY  = 136
};

class Validator
{
    public:

        static void Check(tcp::socket& socket, http::request<http::string_body>& request, u_int8_t draft);
        
        static void IsBody(tcp::socket& socket, http::request<http::string_body>& request);
};



