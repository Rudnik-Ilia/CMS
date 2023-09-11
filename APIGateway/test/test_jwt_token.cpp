#include <iostream>
#include <jwt.h>
#include <ctime>

const std::string token_str = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJkQqdVKP13Wqjs";


// if (jwt_get_alg(parsed_token) == JWT_ALG_HS256 &&
//     jwt_get_grant(parsed_token, "iss") != nullptr &&
//     jwt_get_grant(parsed_token, "sub") != nullptr &&
//     jwt_get_grant(parsed_token, "exp") != nullptr) {

//  g++ test_jwt_token.cpp -ljwt


class JWTMaster
{
    public:
        JWTMaster(const std::string& token): m_parsed_token(nullptr), m_token(token.c_str()), m_is_expired(true), m_is_valid(false) 
        {
            Init();
        }
        JWTMaster(const JWTMaster& other) = delete;
        JWTMaster& operator=(const JWTMaster& other) = delete;
        JWTMaster(JWTMaster&& other) = delete;
        JWTMaster& operator=(JWTMaster&& other) = delete;

        ~JWTMaster()
        {
            jwt_free(m_parsed_token);
        }

        std::string GetStringField(const std::string& field_name)
        {
            if(m_is_valid != false)
            {
                const char* p_field = field_name.c_str();
                return std::string(jwt_get_grant(m_parsed_token, p_field));
            }
            return "";
        }

        bool IsExpired()
        {
            return !m_is_expired;
        }

        bool Check()
        {
            return m_is_expired && m_is_valid;
        }

    private:

        void Init()
        {
            CheckValid();
            CheckExpired();
        }

        void CheckValid()
        {
            int result = jwt_decode(&m_parsed_token, m_token, m_signature, m_size_signature);
            std::cout << result << std::endl;
            if((result == 0) && CheckAlgo())
            {
                std::cout << 'p' << std::endl;
                m_is_valid = true; 
            }
        }

        void CheckExpired()
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

        bool CheckAlgo()
        {
            return (jwt_get_alg(m_parsed_token) == m_algo);
        }

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



int main()
{

    JWTMaster jwt("No token");

    std::cout <<  jwt.GetStringField("role") << std::endl;
    std::cout <<  jwt.IsExpired() << std::endl;
    std::cout <<  jwt.Check() << std::endl;



    

    // jwt_t *parsed_token = nullptr;

    // int result = jwt_decode(&parsed_token, token, key, 38);

    // if (result == 0)
    // {
    //     const char* login_claim = jwt_get_grant(parsed_token, "role");
    //     long exp_claim = jwt_get_grant_int(parsed_token, "exp");
    //     int algo = jwt_get_alg(parsed_token);

    //     if (exp_claim != 0 && login_claim != nullptr && algo == JWT_ALG_HS256)
    //     {
    //         std::cout << login_claim << std::endl;
    //         std::cout << exp_claim << std::endl;

    //         time_t expiration_time = exp_claim;
    //         time_t current_time = std::time(nullptr);

    //         if(expiration_time > current_time)
    //         {
    //             std::cout << "TIME : " << "valid "<< std::endl;
    //         }
    //         else
    //         {
    //             std::cout << "TIME : " << "FAIL"<< std::endl;
    //         }

    //     }
    //     else
    //     {
    //         printf("Some wrong with token!");
    //     }
    // }
    // else
    // {
    //     printf("Cant decode token!");
    // }

    // jwt_free(parsed_token);

    return 0;
}

