#pragma once

#include "../include/helper_functions.hpp"

enum SET_REQUEST: u_int8_t
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
        static bool IsBody(http::request<http::string_body>& request);

        static bool IsGet(http::request<http::string_body>& request);
        static bool IsPost(http::request<http::string_body>& request);
        static bool IsPut(http::request<http::string_body>& request);
        static bool IsDelete(http::request<http::string_body>& request);
        
        static std::string PrintSet()
        {
            std::string result;
            for (int i = 7; i >= 0; --i) 
            {
                result += std::to_string((m_check_map >> i) & 1);
            }
            return result;
        }
        private:
            static u_int8_t m_check_map;
    };


