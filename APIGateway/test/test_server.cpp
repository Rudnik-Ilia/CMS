#include "server.hpp"
#include "router.hpp"
#include "master_request.hpp"
#include "SRP_module.hpp"
#include "irequest.hpp"
#include "crypto_request.hpp"
#include "key_storage.hpp"
#include "big_boo.hpp"
#include "logger.hpp"
// #include "singleton.hpp"




int main() 
{
    BigBoo APP;
   

// ROUTING***************************************************************************************************

    APP.ROUTE("/gateway", 
    {
        Validator(socket, request);
        MasterRequest requestSelf(socket, request);
        requestSelf.ResponseTo(http::status::ok, "I am Big Boo!!!!");
        
        std::this_thread::yield();
    });

    APP.ROUTE("/mix", 
    {
        Validator(socket, request);
        SRP srp;
        Crypto_Request requestSelf(socket, request, srp);
        requestSelf.Process_Mix_Exchange();
        APP.AddMix(requestSelf.GetClientMix(), srp.get_key_asString());
    });

    APP.ROUTE("/signin", 
    {
        Validator(socket, request);
        SRP srp;
        Crypto_Request reqSelf(socket, request, srp);
        reqSelf.Process_JWT_Obtaing();
        reqSelf.ResponseTo(http::status::ok, "I get it");
        // APP.GetKey(reqSelf..GetClientMix());
        // std::string code = SRP::encrypt_by_key("VADIM", "3546317");
        // std::cout << SRP::decrypt_by_key(code, "3546317") << std::endl;
    });

    APP.ROUTE("/mailagent", 
    {
        Validator(socket, request);
        MasterRequest requestSelf(socket, request);
        requestSelf.God_Mode();
        requestSelf.ForwardTo("127.0.0.1", "8008", "rest");
    });

    APP.ROUTE("/items", 
    {
        Validator(socket, request);
        MasterRequest requestSelf(socket, request);
        requestSelf.ForwardTo("127.0.0.1", "8000", "rest");
    });

    APP.ROUTE("/listStorage", 
    {
        Validator(socket, request);
        APP.PrintStorage();
    });

    APP.Run();

    return 0;
}

