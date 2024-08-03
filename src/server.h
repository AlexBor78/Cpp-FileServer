// server.h
#include "Net.h"

#ifndef SERVER_H
#define SERVER_H 1

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
        std::thread ConsoleThread;
        bool isWork;
    private:
        void init();
        void proccess();
    public:
        void start();
        void stop();
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
#endif
