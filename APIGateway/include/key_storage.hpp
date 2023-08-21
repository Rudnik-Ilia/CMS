#pragma once

#include <unordered_map>
#include<mutex>

#include "SRP_module.hpp"

using Iterator = std::unordered_map<std::string, std::string>::iterator; 

class KeyStorage
{
    public:
        explicit KeyStorage();
        KeyStorage(const KeyStorage& other) = delete;
        KeyStorage& operator=(const KeyStorage& other) = delete;
        KeyStorage(KeyStorage&& other) = delete;
        KeyStorage& operator=(KeyStorage&& other) = delete;
        ~KeyStorage();

        void AddKey(std::string client_mix, std::string crypto_key);
        void RemoveKey(std::string client_mix);

        std::string GetKey(std::string client_mix);

        Iterator begin()
        {
            return m_storage.begin();
        }

        Iterator end()
        {
            return m_storage.end();
        }

    private:
        std::unordered_map<std::string, std::string> m_storage;
        std::mutex m_mutex{};

};


