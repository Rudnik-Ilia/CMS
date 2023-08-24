#define RELEASE

#include "helper_functions.hpp"
#include "router.hpp"
#include "master_request.hpp"
#include "SRP_module.hpp"
#include "crypto_request.hpp"
#include "key_storage.hpp"
#include "big_boo.hpp"
#include "logger.hpp"
#include "request_draft.hpp"



int main() 
{
    BigBoo APP;
   
// ROUTING***************************************************************************************************

    APP.ROUTE("/", 
    {
        // Validator_Func(socket, request);
        Drafter drafter;
        drafter.GET();
        MasterRequest requestSelf(socket, request);
        requestSelf.ResponseBack(http::status::ok, "I am Big Boo!!!!");
    });

    APP.ROUTE("/mix", 
    {
        Validator_Func(socket, request);
        SRP srp;
        Crypto_Request requestSelf(socket, request, srp);
        requestSelf.Process_Mix_Exchange();
        APP.AddMix(requestSelf.GetClientMix(), srp.get_key_asString());

    });

    APP.ROUTE("/signin", 
    {
        Validator_Func(socket, request);
        SRP srp;
        Crypto_Request reqSelf(socket, request, srp);
        reqSelf.Process_JWT_Obtaing(APP.GetKey(reqSelf.GetClientMix()));

    });

    APP.ROUTE("/mailagent", 
    {
        Validator_Func(socket, request);
        MasterRequest requestSelf(socket, request);
        requestSelf.God_Mode();
        requestSelf.ForwardTo("127.0.0.1", "8008", "rest");
    });

    APP.ROUTE("/items", 
    {
        Validator_Func(socket, request);
        MasterRequest requestSelf(socket, request);
        requestSelf.ForwardTo("127.0.0.1", "8000", "rest");
    });

// GOD ACTIONS*************************************************
    APP.ROUTE("/listStorage", 
    {
        Validator_Func(socket, request);
        APP.PrintStorage();
    });

    APP.Run();

    return 0;
}

