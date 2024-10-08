// logger.h
#include "Net.h"

#ifndef LOGGER_H
#define LOGGER_H 1

namespace Net
{
    class Logger
    {
    private:
        int16_t LogSize;
        std::string FileName;
        std::fstream logfile;
        std::mutex mtxLog;
    private:
        void init();
        void close();
    public:
        void log(std::string);
        void setName(std::string);
        std::string getName();
    public:
        Logger(std::string);
        Logger();
        ~Logger();
    };
    
} // namespace Net
#endif
