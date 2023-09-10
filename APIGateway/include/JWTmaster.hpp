# pragma once

#include <jwt.h>
#include <ctime>
#include <iostream>


class JWTMaster
{
    public:
        JWTMaster(const std::string& token);
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

const unsigned char JWTMaster::m_signature[] = {"ivwnviewnvakssnvwiu1ewcecenevoiewnvwi"};
int JWTMaster::m_size_signature = sizeof(m_signature);
jwt_alg_t JWTMaster::m_algo = JWT_ALG_HS256;


JWTMaster::JWTMaster(const std::string& token):m_parsed_token(nullptr), m_token(token.c_str()), m_is_expired(true), m_is_valid(false) 
{
    Init();
}

JWTMaster::~JWTMaster()
{

    jwt_free(m_parsed_token);

}

std::string JWTMaster::GetStringField(const std::string& field_name)
{
    if(m_is_valid != false)
    {
        const char* p_field = field_name.c_str();
        return std::string(jwt_get_grant(m_parsed_token, p_field));
    }
    return "";
}


bool JWTMaster::IsExpired()
{
    return !m_is_expired;
}

bool JWTMaster::Check()
{
    return m_is_expired && m_is_valid;
}

void JWTMaster::Init()
{
    CheckValid();
    CheckExpired();
}

void JWTMaster::CheckValid()
{
    int result = jwt_decode(&m_parsed_token, m_token, m_signature, m_size_signature);
    std::cout << result << std::endl;
    if((result == 0) && CheckAlgo())
    {
        std::cout << 'p' << std::endl;
        m_is_valid = true; 
    }
}

void JWTMaster::CheckExpired()
{
    if(m_is_valid)
    {
        long exp_claim = jwt_get_grant_int(m_parsed_token, "exp");
        if(0 != exp_claim)
        {
            m_is_expired = ((time_t)exp_claim > std::time(nullptr));
        }
    }
}

bool JWTMaster::CheckAlgo()
{
    return (jwt_get_alg(m_parsed_token) == m_algo);
}
