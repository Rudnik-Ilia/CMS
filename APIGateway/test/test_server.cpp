#define RELEASE

// #include <yaml-cpp/yaml.h>

#include "helper_functions.hpp"
#include "router.hpp"
#include "master_request.hpp"
#include "SRP_module.hpp"
#include "crypto_request.hpp"
#include "key_storage.hpp"
#include "big_boo.hpp"
#include "logger.hpp"
#include "drafter.hpp"
#include "validator.hpp"




int main() 
{
    // YAML::Node config = YAML::LoadFile("../config/base_config.yaml");
    BigBoo APP;
   
// ROUTING***************************************************************************************************


    APP.ROUTE("/", 
    {
        // Drafter draft;
        // std::cout << Validator::Check(request, draft.GET().dot()) << std::endl;
        MasterRequest requestSelf(socket, request);
        requestSelf.ResponseBack(http::status::ok, "I am Big Boo!!!!");
    });

    APP.ROUTE("/mix", 
    {
        TypeRequest(socket, request);
        SRP srp;
        Crypto_Request requestSelf(socket, request, srp);
        requestSelf.Process_Mix_Exchange();
        APP.AddMix(requestSelf.GetClientMix(), srp.get_key_asString());
    });

    APP.ROUTE("/signin", 
    {
        TypeRequest(socket, request);
        SRP srp;
        Crypto_Request reqSelf(socket, request, srp);
        reqSelf.Process_JWT_Obtaing(APP.GetKey(reqSelf.GetClientMix()));
    });

    APP.ROUTE("/dbmanager", 
    {
        TypeRequest(socket, request);
        MasterRequest requestSelf(socket, request);
        requestSelf.God_Mode();
        requestSelf.ForwardTo(DB_MANAGER_ADDR, DB_MANAGER_PORT, "rest");
    });

    APP.ROUTE("/mailagent", 
    {
        TypeRequest(socket, request);
        MasterRequest requestSelf(socket, request);
        requestSelf.God_Mode();
        requestSelf.ForwardTo(MAIL_AGENT_ADDR, MAIL_AGENT_PORT, "rest");
    });

    APP.ROUTE("/authservice", 
    {
        TypeRequest(socket, request);
        MasterRequest requestSelf(socket, request);
        requestSelf.God_Mode();
        requestSelf.ForwardTo(AUTH_SERV_ADDR, AUTH_SERV_PORT, "rest");
    });


// GOD's ACTIONS****************************************************************

    APP.ROUTE("/listStorage", 
    {
        TypeRequest(socket, request);
        APP.PrintStorage();
    });

// START SERVER******************************************************************

    APP.Run();
    return 0;
}

