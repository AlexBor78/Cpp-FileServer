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
        std::vector<std::thread> clients;
        unsigned int ServAddrLenth;
        std::string ServIPAddr;
        sockaddr_in ServAddr;
        std::mutex Console, mtxClientCounter;
        // std::mutex log; // todo logger
        std::thread ProcessThread;
        int ClientCounter, ServMaxClients;
        //Net::Logger log;
        bool isWork;
    private:
        void init();
        void proccess();
        int ServSend(const int&, void*, unsigned int, int);
        int ServRecv(const int&, void*, unsigned int, int);
        
        int sendSuccess(const int&);
        int sendFail(const int&);
        int recvHead(const int&, Protocol::Head*);
        
        int chekConnection(const int&);
        int recvMsg(const int&, uint32_t);
    public:
        void start();
        void stop();
    public:
        bool isStarted();
        int GetStatus();  
        int getPort();
        std::string getIP();  
    private:
        void Exit(int);
        std::string GetErrorMessage(int);    
    public:
        Server(int, std::string);
        Server();
        ~Server();    
    };
} // namespace Net
#endif
