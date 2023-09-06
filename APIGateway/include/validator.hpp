#pragma once

#include "../include/helper_functions.hpp"
#include "credention.hpp"

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



