#include "../include/SRP_module.hpp"

SRP::SRP()
{
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    boost::random::mt19937 rng(static_cast<unsigned int>(seed));
    boost::random::uniform_int_distribution<big_t> distribution(MIN_VAL, MAX_VAL);
    m_secret = distribution(rng);

    
}

big_t SRP::get_mixture() const
{
    return powm(ROOT, m_secret, PRIME); 
}

void SRP::set_key_for_encode(big_t mix)
{
    m_key = powm(mix, m_secret, PRIME);
    m_s_key = boost::lexical_cast<std::string>(get_key()); 
}

big_t SRP::get_secret() const
{
    return m_secret;
}

big_t SRP::get_key() const
{
    return m_key;
}

std::string SRP::encrypt_by_key(const std::string &plaintext, const std::string &key)
{
    std::string encrypted = plaintext;

    for (size_t i = 0; i < encrypted.length(); ++i)
    {
        encrypted[i] ^= key[i % key.length()];
    }

    return encrypted;
}

std::string SRP::decrypt_by_key(const std::string &cryptotext, const std::string &key)
{
    return encrypt_by_key(cryptotext, key);
}