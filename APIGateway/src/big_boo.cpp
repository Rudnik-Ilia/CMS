#include <boost/asio/ip/address.hpp>
#include "big_boo.hpp"
#include "logger.hpp"


std::atomic<bool> BigBoo::m_stop_flag(true);

BigBoo::BigBoo(std::string ip_addr, int port): m_acceptor(m_ioContext, tcp::endpoint(net::ip::make_address(ip_addr), port)), m_router(), m_keyStorage()
{
    std::signal(SIGINT, BigBoo::StopHandler);
    LOGINFO(start);
    LOGINFO("server run on [" + m_acceptor.local_endpoint().address().to_string() + ':' + std::to_string(m_acceptor.local_endpoint().port()) +"]");
}

BigBoo::~BigBoo()
{
    m_acceptor.close();
    LOGINFO(end);
}

void BigBoo::Routing(const std::string& path, std::function<void(http::request<http::string_body>&, tcp::socket&)> handler)
{
    m_router.AddRoute(path, handler);
}

void BigBoo::Run() try
{
    while(m_stop_flag.load())
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
    m_acceptor.close();
}
catch(const BadAppleExeption& e)
{
    sleep(3);
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

void BigBoo::StopHandler(int signal)
{
    if(signal == SIGINT)
    {
        LOGINFO("Stopping server...");
        m_stop_flag.store(false);
        throw BadAppleExeption("EXIT");
    }
}