#include "server.hpp"
#include "router.hpp"





int main() 
{
    net::io_context ioContext;
    tcp::acceptor acceptor(ioContext, tcp::endpoint(tcp::v4(), 9090));

    Router router;

    router.AddRoute("/mix", [](http::request<http::string_body>& request, tcp::socket& socket)
    {
        std::cout << "MIX" << std::endl;
    });

    router.AddRoute("/signin", [](http::request<http::string_body>& request, tcp::socket& socket)
    {
        std::cout << "SIGNIN" << std::endl;
    });


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

    return 0;
}


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
    // acceptor.close();