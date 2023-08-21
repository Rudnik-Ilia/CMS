#pragma once

#include "../include/server.hpp"
#include "../include/irequest.hpp"

class MasterRequest : public IRequest
{
    public:
        explicit MasterRequest(tcp::socket& socket, http::request<http::string_body>& request);
        MasterRequest(const MasterRequest& other);
        MasterRequest& operator=(const MasterRequest& other) = delete;
        MasterRequest(MasterRequest&& other) = delete;
        MasterRequest& operator=(MasterRequest&& other) = delete;
        ~MasterRequest();

        void RequestTo(const std::string& HOST, const std::string& PORT, const std::string& rest_of_path) override;

        void ResponseTo(http::status status, const std::string& body) override;
        void ForwardTo(const std::string& HOST, const std::string& PORT, const std::string& rest_of_path) override;
        void Get_Token();

        int Check_Token(std::string token);

        bool Authorized();

        void God_Mode()
        {
            m_authorized = true;
        }

    private:
        std::string m_token;
        bool m_authorized;
        tcp::socket& m_socket;
        http::request<http::string_body>& m_request;
};