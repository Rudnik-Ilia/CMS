#include <boost/asio/ip/address.hpp>
#include "big_boo.hpp"
#include "logger.hpp"



BigBoo::BigBoo(std::string ip_addr, int port): m_acceptor(m_ioContext, tcp::endpoint(net::ip::make_address(ip_addr), port)), m_router(), m_keyStorage(), m_logger("log.txt")
{
    CONSOLE_LOG("server run on [" + m_acceptor.local_endpoint().address().to_string() + ':' + std::to_string(m_acceptor.local_endpoint().port()) +"]");
}

BigBoo::~BigBoo()
{
    m_acceptor.close();
}

void BigBoo::Routing(const std::string& path, std::function<void(http::request<http::string_body>&, tcp::socket&)> handler)
{
    m_router.AddRoute(path, handler);
}

void BigBoo::Run()
{
    while(true)
    {
        tcp::socket socket(m_ioContext);
        m_acceptor.accept(socket);

        std::thread([socket = std::move(socket), this]() mutable
        {
            try
            {
                this->m_router.HandleSocket(socket);
            }
            catch(const std::exception& e)
            {
                std::cerr << "Main Loop: " << e.what() << '\n';
            }

        }).detach();
    }
}

void BigBoo::AddMix(std::string clientMix, std::string secretKey)
{
    m_keyStorage.AddKey(clientMix, secretKey);
}


std::string BigBoo::GetKey(const std::string clientMix)
{
    return  m_keyStorage.GetKey(clientMix);
}


// TEMPORALY************************************************
void BigBoo::PrintStorage()
{
    for(const auto &item : m_keyStorage)
    {
        std::cout << item.first << ' ' << item.second << std::endl;
    }
}