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
    return (power(ROOT, m_secret)) % PRIME; 
}

big_t SRP::get_key_for_encode(big_t mix) const
{
    return (power(mix, m_secret)) % PRIME; 
}

big_t SRP::get_secret() const
{
    return m_secret;
}