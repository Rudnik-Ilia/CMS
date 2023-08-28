// #include "validator.hpp"
// #include "logger.hpp"

// enum METHODS: u_int8_t
// {
//     GET_METHOD = 0,
//     POST_METHOD = 1,
//     PUT_METHOD = 2,
//     DELETE_METHOD = 3
// };

// u_int8_t Validator::m_check_map = 0;

// bool Validator::Check(http::request<http::string_body>& request, u_int8_t draft)
// {
//     m_check_map &= 0;
//     m_check_map |= (IsBody(request) << 7);  
//     m_check_map |= IsGet(request);  
//     m_check_map |= (1 * IsPost(request)) << (POST_METHOD);  
//     m_check_map |= (1 * IsPut(request)) << (PUT_METHOD);  
//     m_check_map |= (1 * IsDelete(request)) << (DELETE_METHOD); 

//     return !(m_check_map ^ draft);
// }

// bool Validator::IsBody(http::request<http::string_body>& request)
// {
//     return !request.body().empty();
// }

// bool Validator::IsGet(http::request<http::string_body>& request)
// {
//     return (request.method() == http::verb::get);
// }

// bool Validator::IsPost(http::request<http::string_body>& request)
// {
//     return (request.method() == http::verb::post);
// }

// bool Validator::IsPut(http::request<http::string_body>& request)
// {
//     return (request.method() == http::verb::put);
// }

// bool Validator::IsDelete(http::request<http::string_body>& request)
// {
//     return (request.method() == http::verb::delete_);
// }
