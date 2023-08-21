#include "big_boo.hpp"


BigBoo::BigBoo(int port): m_acceptor(m_ioContext, tcp::endpoint(tcp::v4(), port)), m_router(), m_keyStorage()
{

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
