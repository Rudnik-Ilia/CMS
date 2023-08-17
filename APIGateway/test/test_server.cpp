#include "server.hpp"
#include "router.hpp"
#include "master_request.hpp"





int main() 
{
    net::io_context ioContext;
    tcp::acceptor acceptor(ioContext, tcp::endpoint(tcp::v4(), 9090));

// ROUTING***************************************************************************************************

    Router router;
    router.AddRoute("/gateway", [](http::request<http::string_body>& request, tcp::socket& socket)
    {
        std::cout << "MIX" << std::endl;
        Define_type_Request(request);
        MasterRequest requestSelf(socket, request);
        requestSelf.ResponseTo(http::status::ok, "I am Big Boo!");
    });

    router.AddRoute("/mix", [](http::request<http::string_body>& request, tcp::socket& socket)
    {
        std::cout << "MIX" << std::endl;
        Define_type_Request(request);
        MasterRequest requestSelf(socket, request);

    });

    router.AddRoute("/signin", [](http::request<http::string_body>& request, tcp::socket& socket)
    {
        std::cout << "SIGNIN" << std::endl;
        Define_type_Request(request);
    });

    router.AddRoute("/mailagent", [](http::request<http::string_body>& request, tcp::socket& socket)
    {
        std::cout << "SIGNIN" << std::endl;
        Define_type_Request(request);
        MasterRequest requestSelf(socket, request);
        requestSelf.ForwardTo("127.0.0.1", "8008", "rest");
    });

    router.AddRoute("/items", [](http::request<http::string_body>& request, tcp::socket& socket)
    {
        std::cout << "SIGNIN" << std::endl;
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
 