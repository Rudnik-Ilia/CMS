#include "header.hpp"



int main() 
{
    net::io_context ioContext;
    tcp::acceptor acceptor(ioContext, tcp::endpoint(tcp::v4(), 9090));

    while(true)
    {
        try
        {
            tcp::socket socket(ioContext);
            acceptor.accept(socket);

            std::thread(&Handle_Connection, std::move(socket)).detach();
            
        }
        catch(const std::exception& e)
        {
            std::cerr << "Main Loop: " << e.what() << '\n';
        }

    }
    acceptor.close();


    // while(true) 
    // {
    //     tcp::socket socket(ioContext);
    //     acceptor.accept(socket);

    //     beast::flat_buffer buffer;
    //     http::request<http::string_body> request;
    //     http::read(socket, buffer, request);

    //     std::string restOfURL = request.target().to_string();
    //     std::string begin_of_URL = restOfURL.substr(1, PATH.length() - 1);
    //     restOfURL.erase(0, PATH.length());

    //     http::response<http::string_body> response;
    //     if(begin_of_URL == "app1/")
    //     {
    //         std::cout << begin_of_URL << std::endl;
    //         std::cout << restOfURL << std::endl;
    //         std::string responseBody = forwardRequest(HOST, PORT, restOfURL);

    //         json reply = json::parse(responseBody);

    //         http::response<http::string_body> response{http::status::ok, request.version()};
    //         response.set(http::field::server, BOOST_BEAST_VERSION_STRING);
    //         response.set(http::field::content_type, "text/html");
    //         response.body() = reply.dump();
    //         response.prepare_payload();

    //         http::write(socket, response);
    //     }
    //     else if(begin_of_URL == "app2/")
    //     {
    //         std::cout << begin_of_URL << std::endl;
    //         std::cout << restOfURL << std::endl;
    //     }

    //     boost::beast::http::write(socket, response);
    //     socket.shutdown(boost::asio::ip::tcp::socket::shutdown_send);
    // }

    return 0;
}
