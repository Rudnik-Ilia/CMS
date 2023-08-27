#include "validator.hpp"
#include "logger.hpp"

enum METHODS: u_int8_t
{
    GET_METHOD = 0,
    POST_METHOD = 1,
    PUT_METHOD = 2,
    DELETE_METHOD = 3
};

u_int8_t Validator::m_check_map = 0;


void Validator::Check(tcp::socket& socket, http::request<http::string_body>& request, u_int8_t draft)
{

    m_check_map &= 0;

    m_check_map |= (IsBody(request) << 7);  
    // std::cout << IsBody(request) << std::endl; 

    // m_check_map |= IsGet(request);  
    // std::cout << IsGet(request) << std::endl;

    m_check_map |= (IsPost(request) * POST_METHOD);  

    std::cout << (IsPost(request) * POST_METHOD) << std::endl;

    // m_check_map |= (1 << (IsPut(request) * PUT_METHOD));  
    // std::cout << (IsPut(request) * PUT_METHOD) << std::endl;

    // m_check_map |= (1 << (IsDelete(request) * DELETE_METHOD)); 
    std::cout << (IsDelete(request) * DELETE_METHOD) << std::endl;


}

bool Validator::IsBody(http::request<http::string_body>& request)
{
    return !request.body().empty();
}

bool Validator::IsGet(http::request<http::string_body>& request)
{
    return (request.method() == http::verb::get);
}

bool Validator::IsPost(http::request<http::string_body>& request)
{
    return (request.method() == http::verb::post);
}

bool Validator::IsPut(http::request<http::string_body>& request)
{
    return (request.method() == http::verb::put);
}

bool Validator::IsDelete(http::request<http::string_body>& request)
{
    return (request.method() == http::verb::delete_);
}
// int Validator::IsGet(http::request<http::string_body>& request)
// {
//     return ((request.method() == http::verb::get) * GET_METHOD);
// }

// int  Validator::IsPost(http::request<http::string_body>& request)
// {
//     return ((request.method() == http::verb::post) * POST_METHOD);
// }

// int Validator::IsPut(http::request<http::string_body>& request)
// {
//     return ((request.method() == http::verb::put) * PUT_METHOD);
// }

// int Validator::IsDelete(http::request<http::string_body>& request)
// {
//     return ((request.method() == http::verb::delete_) * DELETE_METHOD);
// }