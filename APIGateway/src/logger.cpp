#include "logger.hpp"

Logger::Logger(const std::string &filename) : m_logFile(filename, std::ios::in) 
{
    if (!m_logFile.is_open()) 
    {
        m_logFile.open(filename);
    }
}

Logger::~Logger()
{
    m_logFile.close();
}

