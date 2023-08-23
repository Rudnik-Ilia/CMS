#pragma once

#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include <iomanip>

#include "singleton.hpp"

#define LOGFILE ("log.txt")
#define CONSOLE_LOG(message) Singleton<Logger>::GetInstance(LOGFILE)->LogToConsole(message)

class Logger final
{
    public:
        explicit Logger(const std::string &filename);
        Logger(const Logger& other) = delete;
        Logger& operator=(const Logger& other) = delete;
        Logger(Logger&& other) = delete;
        Logger&& operator=(Logger&& other) = delete;
        ~Logger();

        template <typename T>
        void LogToFile(const T &message);

        template <typename T>
        void LogToConsole(const T &message);

    private:
        std::ofstream m_logFile;
};

template<typename T>
void Logger::LogToFile(const T &message)
{
    auto now = std::chrono::system_clock::now();
    auto now_c = std::chrono::system_clock::to_time_t(now);

    m_logFile << "[" << std::put_time(std::localtime(&now_c), "%Y-%m-%d %H:%M:%S") << "] " << message << std::endl;
}

template<typename T>
void Logger::LogToConsole(const T &message)
{
    auto now = std::chrono::system_clock::now();
    auto now_c = std::chrono::system_clock::to_time_t(now);

    std::cout << "[" << std::put_time(std::localtime(&now_c), "%Y-%m-%d %H:%M:%S") << "] " << message << std::endl;
}





