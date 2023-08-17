#include "server.hpp"
#include "router.hpp"
#include "master_request.hpp"
#include "SRP_module.hpp"
#include "irequest.hpp"
#include "crypto_request.hpp"





int main() 
{
    net::io_context ioContext;
    tcp::acceptor acceptor(ioContext, tcp::endpoint(tcp::v4(), 9090));

// ROUTING***************************************************************************************************

    Router router;

    router.AddRoute("/gateway", [](http::request<http::string_body>& request, tcp::socket& socket)
    {
        Define_type_Request(request);
        MasterRequest requestSelf(socket, request);
        requestSelf.ResponseTo(http::status::ok, "I am Big Boo!");
    });

    router.AddRoute("/mix", [](http::request<http::string_body>& request, tcp::socket& socket)
    {
        Define_type_Request(request);
        SRP srp;
        Crypto_Request requestSelf(socket, request, srp);
    });

    router.AddRoute("/signin", [](http::request<http::string_body>& request, tcp::socket& socket)
    {
        Define_type_Request(request);
    });

    router.AddRoute("/mailagent", [](http::request<http::string_body>& request, tcp::socket& socket)
    {
        Define_type_Request(request);
        MasterRequest requestSelf(socket, request);

        if(requestSelf.Authorized())
        {
            requestSelf.ForwardTo("127.0.0.1", "8008", "rest");
        }
        else
        {
            requestSelf.ResponseTo(http::status::unauthorized, "You need to have a token!");
        }
    });

    router.AddRoute("/items", [](http::request<http::string_body>& request, tcp::socket& socket)
    {
        Define_type_Request(request);
        MasterRequest requestSelf(socket, request);
        requestSelf.ForwardTo("127.0.0.1", "8000", "rest");
    });

// MAINLOOP**************************************************************************************************

    while(true)
    {
        tcp::socket socket(ioContext);
        acceptor.accept(socket);

        std::thread([socket = std::move(socket), &router]() mutable
        {
            try
            {
                router.Run(socket);
            }
            catch(const std::exception& e)
            {
                std::cerr << "Main Loop: " << e.what() << '\n';
            }

        }).detach();
    }

    acceptor.close();

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
 