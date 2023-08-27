#include "key_storage.hpp"
#include "logger.hpp"


KeyStorage::KeyStorage(): m_storage(){}

KeyStorage::~KeyStorage(){}

void KeyStorage::AddKey(std::string client_mix, std::string crypto_key)
{
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_storage[client_mix] = crypto_key;
    }
}

// void KeyStorage::RemoveKey(std::string client_mix)
// {
//     {
//         std::lock_guard<std::mutex> lock(m_mutex);

//         auto item = m_storage.find(client_mix);
//         if(item != m_storage.end())
//         {
//             m_storage.erase(client_mix);
//         }
//     }
// }

std::string KeyStorage::GetKey(const std::string client_mix)
{
    {
        std::lock_guard<std::mutex> lock(m_mutex); 
        auto item = m_storage.find(client_mix);
        if(item != m_storage.end())
        {
            m_storage.erase(client_mix);
            return item->second;
        }
        return "";
    }
}