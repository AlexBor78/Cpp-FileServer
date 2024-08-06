#pragma once
#include "logger.h"

namespace Net
{
    Logger::~Logger()
    {
        close();
    }
    Logger::Logger(std::string name, int maxsize)
    :
    LogSize(0),
    MaxLogSize(maxsize),
    FileName(name),
    logfile(),
    mtxLog()
    {}
    Logger::Logger(std::string name)
    :
    LogSize(0),
    MaxLogSize(10000),
    FileName(name),
    logfile(),
    mtxLog()
    {}
    Logger::Logger()
    :
    LogSize(0),
    MaxLogSize(10000),
    FileName("LogFile"),
    logfile(),
    mtxLog()
    {}

    void Logger::init()
    {
        if(FileName.empty())
        {
            throw("Logger error: FileName is empty");
        }
        if(MaxLogSize < 0)
        {
            throw("Logger error: MaxLogSize < 0");
        }
        if(logfile.is_open())
        {
            logfile.close();
        }

        logfile.open(FileName, std::ios::app);
        LogSize = 0;
        log("LogFile \"" + FileName +  "\" succes opened");
    }

    void Logger::close()
    {
        if(!logfile.is_open())
        {
            return;
        }
        mtxLog.lock();
        logfile.close();
        mtxLog.unlock();
    }

    void Logger::log(std::string msg)
    {
        if(!logfile.is_open())
        {
            init();
        }
        if(LogSize > MaxLogSize)
        {
            FileName = FileName + "2";
            mtxLog.lock();
            LogSize = 0;
            mtxLog.unlock();
            init();
        }

        mtxLog.lock();
        logfile << "thread id: " << std::this_thread::get_id() << " " << msg << std::endl;
        LogSize++;
        mtxLog.unlock();
    }

    void Logger::setName(std::string name)
    {
        FileName = name;
    }
    std::string Logger::getName()
    {
        return FileName;
    }

    void Logger::setMaxLogSize(int maxsize)
    {
        MaxLogSize = maxsize;
    }
    int Logger::getMaxLogSize()
    {
        return MaxLogSize;
    }
} // namespace Net