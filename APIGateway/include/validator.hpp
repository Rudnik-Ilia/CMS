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

enum METHODS: u_int8_t
{
    GET_METHOD = 0,
    POST_METHOD = 1,
    PUT_METHOD = 2,
    DELETE_METHOD = 3
};

class Validator
{
    public:
        static inline bool Check(http::request<http::string_body>& request, u_int8_t draft)
        {
            u_int8_t m_check_map = 0;
            m_check_map |= (IsBody(request) << 7);  
            m_check_map |= IsGet(request);  
            m_check_map |= (1 * IsPost(request)) << (POST_METHOD);  
            m_check_map |= (1 * IsPut(request)) << (PUT_METHOD);  
            m_check_map |= (1 * IsDelete(request)) << (DELETE_METHOD); 

            return !(m_check_map ^ draft);
        }

        static inline bool IsBody(http::request<http::string_body>& request)
        {
            return !request.body().empty();
        }

        static inline bool IsGet(http::request<http::string_body>& request)
        {
            return (request.method() == http::verb::get);
        }

        static inline bool IsPost(http::request<http::string_body>& request)
        {
            return (request.method() == http::verb::post);
        }

        static inline bool IsPut(http::request<http::string_body>& request)
        {
            return (request.method() == http::verb::put);
        }

        static inline bool IsDelete(http::request<http::string_body>& request)
        {
            return (request.method() == http::verb::delete_);
        }

        
        // TEMPORALY FOR TEST ***************************
        // static std::string PrintSet()
        // {
        //     std::string result;
        //     for (int i = 7; i >= 0; --i) 
        //     {
        //         result += std::to_string((m_check_map >> i) & 1);
        //     }
        //     return result;
        // }
        // private:
        //     static u_int8_t m_check_map;
};



