#include "server.hpp"
#include "router.hpp"
#include "master_request.hpp"
#include "SRP_module.hpp"
#include "irequest.hpp"
#include "crypto_request.hpp"
#include "key_storage.hpp"
#include "big_boo.hpp"


int main() 
{
    BigBoo APP(9090);

// ROUTING***************************************************************************************************

    APP.ROUTE("/gateway", 
    {
        Define_type_Request(request);
        MasterRequest requestSelf(socket, request);
        requestSelf.ResponseTo(http::status::ok, "I am Big Boo!");
    });

    APP.ROUTE("/mix", 
    {
        Define_type_Request(request);

        SRP srp;

        Crypto_Request requestSelf(socket, request, srp);
        requestSelf.Process_Authorizing();

        APP.AddMix(requestSelf.GetClientMix(), srp.get_key_asString());
    });

    APP.ROUTE("/signin", 
    {
        Define_type_Request(request);
    });

    APP.ROUTE("/mailagent", 
    {
        Define_type_Request(request);
        MasterRequest requestSelf(socket, request);
        requestSelf.God_Mode();
        requestSelf.ForwardTo("127.0.0.1", "8008", "rest");
    });

    APP.ROUTE("/items", 
    {
        Define_type_Request(request);
        MasterRequest requestSelf(socket, request);
        requestSelf.ForwardTo("127.0.0.1", "8000", "rest");
    });

    APP.ROUTE("/listStorage", 
    {
        Define_type_Request(request);

        APP.PrintStorage();
    });

    APP.Run();

    return 0;
}

// OLDLOOP***********************************************************************************

    // while(true)
    // {
    //     try
    //     {
    //         tcp::socket socket(ioContext);
    //         acceptor.accept(socket);

    //         std::thread(&Handle_Connection, std::move(socket)).detach();
    //     }
    //     catch(const std::exception& e)
    //     {
    //         std::cerr << "Main Loop: " << e.what() << '\n';
    //     }
    // }

//OLD SERVER***************************************************************************************
    // net::io_context ioContext;
    // tcp::acceptor acceptor(ioContext, tcp::endpoint(tcp::v4(), 9090));
   // Router router;
   // ROUTING***************************************************************************************************



    //    APP.Routing("/m", [](http::request<http::string_body>& request, tcp::socket& socket)
    // {
    //     Define_type_Request(request);

    //     SRP srp;
    //     Crypto_Request requestSelf(socket, request, srp);
    //     requestSelf.Process_Authorizing();

    // });
     // router.AddRoute("/gateway", [](http::request<http::string_body>& request, tcp::socket& socket)
    // {
    //     Define_type_Request(request);

    //     MasterRequest requestSelf(socket, request);
    //     requestSelf.ResponseTo(http::status::ok, "I am Big Boo!");
    // });

    // router.AddRoute("/mix", [](http::request<http::string_body>& request, tcp::socket& socket)
    // {
    //     Define_type_Request(request);

    //     SRP srp;
    //     Crypto_Request requestSelf(socket, request, srp);
    //     requestSelf.Process_Authorizing();
    // });

    // router.AddRoute("/signin", [](http::request<http::string_body>& request, tcp::socket& socket)
    // {
    //     Define_type_Request(request);
    // });

    // router.AddRoute("/mailagent", [](http::request<http::string_body>& request, tcp::socket& socket)
    // {
    //     Define_type_Request(request);

    //     MasterRequest requestSelf(socket, request);
    //     requestSelf.God_Mode();
    //     requestSelf.ForwardTo("127.0.0.1", "8008", "rest");
    // });

    // router.AddRoute("/items", [](http::request<http::string_body>& request, tcp::socket& socket)
    // {
    //     Define_type_Request(request);

    //     MasterRequest requestSelf(socket, request);
    //     requestSelf.ForwardTo("127.0.0.1", "8000", "rest");
    // });

// MAINLOOP**************************************************************************************************
    // while(true)
    // {
    //     tcp::socket socket(ioContext);
    //     acceptor.accept(socket);

    //     std::thread([socket = std::move(socket), &router]() mutable
    //     {
    //         try
    //         {
    //             router.HandleSocket(socket);
    //         }
    //         catch(const std::exception& e)
    //         {
    //             std::cerr << "Main Loop: " << e.what() << '\n';
    //         }

    //     }).detach();
    // }

    // acceptor.close();