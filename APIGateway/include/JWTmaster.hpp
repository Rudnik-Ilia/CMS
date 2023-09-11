# pragma once

#include <jwt.h>
#include <ctime>
#include <iostream>


class JWTMaster
{
    public:
        explicit JWTMaster(const std::string& token);
        JWTMaster(const JWTMaster& other) = delete;
        JWTMaster& operator=(const JWTMaster& other) = delete;
        JWTMaster(JWTMaster&& other) = delete;
        JWTMaster& operator=(JWTMaster&& other) = delete;
        ~JWTMaster();

        std::string GetStringField(const std::string& field_name);

        bool IsExpired();
        bool Check();

    private:
        void Init();
        void CheckValid();
        void CheckExpired();
        bool CheckAlgo();

        jwt_t * m_parsed_token;
        const char * m_token;
        bool m_is_expired;
        bool m_is_valid; 

        static const unsigned char m_signature[];
        static int m_size_signature; 
        static jwt_alg_t m_algo;
};