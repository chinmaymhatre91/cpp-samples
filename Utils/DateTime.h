#ifndef UTILS_DATETIME
#define UTILS_DATETIME

#include <iostream>
#include <sstream>
#include <chrono>
#include <iomanip>

namespace Utils
{
    namespace DateTime
    {
        std::string getCurrentTime()
        {
            auto t = std::chrono::system_clock::now();
            std::time_t t_time_t = std::chrono::system_clock::to_time_t(t);
            //return std::ctime(&t_time_t); 
            std::tm tm  = *std::localtime(&t_time_t);
            std::stringstream ss;
            ss << std::put_time(&tm, "%D %T");
            return ss.str();
        } 
    }
}

#endif
