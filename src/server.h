// server.h
#pragma once
#include "Net.h"

namespace Net
{
    class Server
    {
    private:
        int ServSock, ServPort, ServStatus;
        unsigned int ServAddrLenth;
        std::string ServIPAddr;
        sockaddr_in ServAddr;
        std::mutex Console;
        std::thread ServProccess;
    private:
        void init();
        void proccess();
    public:
        void start();
        void stop();
        //void send()
    public:
        bool isStarted();
        int GetStatus();  
        int getPort();
        std::string getIP();  
    private:
        void Exit(int, std::string);
        void Exit(int);
        void Exit();
        std::string GetErrorMessage(int);    
    public:
        Server(int, std::string);
        Server();
        ~Server();    
    };
} // namespace Net
