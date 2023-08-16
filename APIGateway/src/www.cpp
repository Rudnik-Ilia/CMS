#include <boost/beast.hpp>
#include <boost/asio.hpp>
#include <iostream>
#include <map>
#include <functional>

namespace net = boost::asio;
namespace http = boost::beast::http;
using tcp = net::ip::tcp;

class Router {
public:
    void addRoute(const std::string& path, std::function<void(http::request<http::string_body>&, tcp::socket&)> handler) {
        routes_[path] = std::move(handler);
    }

    void routeRequest(http::request<http::string_body>& request, tcp::socket& socket) {
        auto it = routes_.find(request.target().to_string());
        if (it != routes_.end()) {
            it->second(request, socket);
        } else {
            handleNotFound(request, socket);
        }
    }

private:
    std::map<std::string, std::function<void(http::request<http::string_body>&, tcp::socket&)>> routes_;

    void handleNotFound(http::request<http::string_body>& request, tcp::socket& socket) {
        http::response<http::string_body> response;
        response.version(request.version());
        response.status(http::status::not_found);
        response.set(http::field::server, "Boost.Beast Web Server");
        response.set(http::field::content_type, "text/plain");
        response.body() = "Not Found";
        response.content_length(response.body().size());

        http::write(socket, response);
    }
};

int main() {
    net::io_context ioContext;
    tcp::acceptor acceptor(ioContext, tcp::endpoint(tcp::v4(), 8080));

    Router router;
    router.addRoute("/hello", [](http::request<http::string_body>& request, tcp::socket& socket) {
        http::response<http::string_body> response;
        response.body() = "Hello, World!";
        // ... Set other response fields ...

        http::write(socket, response);
    });

    router.addRoute("/bye", [](http::request<http::string_body>& request, tcp::socket& socket) {
        http::response<http::string_body> response;
        response.body() = "Goodbye!";
        // ... Set other response fields ...

        http::write(socket, response);
    });

    while (true) {
        tcp::socket socket(ioContext);
        acceptor.accept(socket);

        net::spawn(ioContext, [&socket, &router](net::yield_context yield) {
            try {
                boost::beast::flat_buffer buffer;
                http::request<http::string_body> request;

                http::async_read(socket, buffer, request, yield);

                router.routeRequest(request, socket);

                socket.shutdown(tcp::socket::shutdown_send);
            } catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        });
    }

    return 0;
}
