#pragma once


#include <memory>
#include "helper_functions.hpp"
#include "credention.hpp"
#include "JWTmaster.hpp"

class MasterRequest
{
    public:
        explicit MasterRequest(tcp::socket& socket, http::request<http::string_body>& request);
        MasterRequest(const MasterRequest& other);
        MasterRequest& operator=(const MasterRequest& other) = delete;
        MasterRequest(MasterRequest&& other) = delete;
        MasterRequest& operator=(MasterRequest&& other) = delete;
        ~MasterRequest();

        // void RequestTo(const std::string& HOST, const std::string& PORT, const std::string& rest_of_path);

        void ResponseBack(http::status status, const std::string& body);
        void ForwardTo(const std::string& HOST, const std::string& PORT, const std::string& body);

        void Get_Token();
        bool Authorized();

// TEMPORALY FOR TESTING
        void God_Mode()
        {
            m_authorized = true;
        }

    private:
        std::string m_token;

        bool m_authorized;
        tcp::socket& m_socket;
        http::request<http::string_body>& m_request;
        
        std::unique_ptr<JWTMaster> m_jwt_master;
};
