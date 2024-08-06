// logger.h
#pragma once
#include "Net.h"

#ifndef LOGGGER_H
#define LOGGER_H 1

namespace Net
{
    class Logger
    {
    private:
        int16_t MaxLogSize, LogSize;
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
        void setMaxLogSize(int);
        int getMaxLogSize();
    public:
        Logger(std::string, int);
        Logger(std::string);
        Logger();
        ~Logger();
    };
    
} // namespace Net
#endif
