#include <iostream>
#include <jwt.h>
#include <ctime>

const char *token = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJyb2xlIjoiYWRtaW4iLCJleHAiOjE2OTM5ODY3Nzh9.hUNcCEFF__nhce6zTY2yKjB34-EWMyQG2lIVN7HNJRI";
const std::string token_str = "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9.eyJyb2xlIjoiYWRtaW4iLCJleHAiOjE2OTM5ODY3Nzh9.hUNcCEFF__nhce6zTY2yKjB34-EWMyQG2lIVN7HNJRI";
const unsigned char key[] = "ivwnviewnvakssnvwiu1ewcecenevoiewnvwi";

// if (jwt_get_alg(parsed_token) == JWT_ALG_HS256 &&
//     jwt_get_grant(parsed_token, "iss") != nullptr &&
//     jwt_get_grant(parsed_token, "sub") != nullptr &&
//     jwt_get_grant(parsed_token, "exp") != nullptr) {

//  g++ test_jwt_token.cpp -ljwt


class JWTMaster
{
    public:
        JWTMaster(const std::string& token): m_parsed_token(nullptr), m_token(token.c_str()){}
        JWTMaster(const JWTMaster& other) = delete;
        JWTMaster& operator=(const JWTMaster& other) = delete;
        JWTMaster(JWTMaster&& other) = delete;
        JWTMaster& operator=(JWTMaster&& other) = delete;


        ~JWTMaster()
        {
            jwt_free(m_parsed_token);
        }

        int Decode_Token()
        {
            int result = jwt_decode(&m_parsed_token, m_token, m_signature, m_size_signature);
            return result;
        }

    private:
        jwt_t * m_parsed_token;
        const char * m_token;
        static const unsigned char m_signature[];
        static int m_size_signature;   
};

const unsigned char JWTMaster::m_signature[] = {"ivwnviewnvakssnvwiu1ewcecenevoiewnvwi"};
int JWTMaster::m_size_signature = sizeof(m_signature);


enum SS: u_int8_t
{
    ADMIN = 0b00000000,
    MANAGER = 0b10000001

};

int main()
{

    JWTMaster jwt(token_str);

    if(!jwt.Decode_Token())
    {
        std::cout << "Fine" << std::endl;
    }
    else
    {
        std::cout << "Wrong" << std::endl;
    }
    
    std::cout << MANAGER << std::endl;









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

