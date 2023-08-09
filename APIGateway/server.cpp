#include <iostream>
#include <boost/asio.hpp>
#include <boost/beast.hpp>
#include <boost/beast/http.hpp>


namespace asio = boost::asio;       
namespace http = boost::beast::http; 

using tcp = boost::asio::ip::tcp;

// g++ -std=c++11 -lpthread

void Request_APP_1(const http::request<http::string_body>& request, http::response<http::string_body>& response) 
{
    response.version(request.version());
    response.result(http::status::ok);
    response.set(http::field::server, "Boost.Beast HTTP Server");
    response.set(http::field::content_type, "text/plain");
    response.body() = response.body();
    response.prepare_payload();

}




void Reply_404(const http::request<http::string_body>& request, http::response<http::string_body>& response) 
{
    response.version(request.version());
    response.result(http::status::not_found);
    response.set(http::field::server, "Boost.Beast HTTP Server");
    response.set(http::field::content_type, "text/plain");
    response.body() = "404 Not Found";
    response.prepare_payload();
}
void handleBye(const http::request<http::string_body>& request, http::response<http::string_body>& response) 
{
    std::cout << request.target();
    response.version(request.version());
    response.result(http::status::ok);
    response.set(http::field::server, "Boost.Beast HTTP Server");
    response.set(http::field::content_type, "text/plain");
    response.body() = "Goodbye from the /bye route!";
    response.prepare_payload();
}



int main()
{
        asio::io_context io_context;
        asio::ip::tcp::acceptor acceptor(io_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 9090));

        while(true) 
        {
            asio::ip::tcp::socket socket(io_context);
            acceptor.accept(socket);

            boost::beast::flat_buffer buffer;
            http::request<http::string_body> request;

            http::read(socket, buffer, request);
            http::response<http::string_body> response;

            if (request.target() == "/app1") 
            {
                try
                {
                    tcp::resolver resolver(io_context);
                    auto results = resolver.resolve("localhost", "8000");
                    
                    boost::beast::tcp_stream stream(io_context);
                    stream.connect(results);

                    http::request<http::string_body> request{http::verb::get, "/items", 11};
                    request.set(http::field::host, "localhost");
                    request.set(http::field::user_agent, "My-C++-Client");

                    http::write(stream, request);
                    boost::beast::flat_buffer buffer;
                    http::response<http::string_body> res;
                    http::read(stream, buffer, res);

                    Request_APP_1(request, response);   
                    http::write(socket, response);
                }
                catch (std::exception const& e) 
                {
                    std::cerr << "Exception: " << e.what() << std::endl;
                }
            } 
            else if(request.target() == "/app2") 
            {
                handleBye(request, response);
                std::cout << request.target();
            } 
            else 
            {
                Reply_404(request, response);
            }

            http::write(socket, response);
            socket.shutdown(asio::ip::tcp::socket::shutdown_send);
        }

    return 0;

} 