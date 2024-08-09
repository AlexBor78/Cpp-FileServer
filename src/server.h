// server.h
#include "Net.h"

#ifndef SERVER_H
#define SERVER_H 1

namespace Net
{
    class Server
    {
    private:
        int ServSock{-1}, ServPort{-1}, ServStatus{0};
        sockaddr_in ServAddr{0};
        unsigned int ServAddrLenth{sizeof(ServAddr)};
        std::string ServIPAddr;
        
        std::mutex Console, mtxClientCounter, mtxDataFile;
        std::vector<std::thread> clients{};
        std::thread ProcessThread;

        int ClientCounter, ServMaxQueue{SERVER_MAX_CLIENTS_QUEUE};
        
        std::fstream DataFile;
        Net::Logger log{SERVER_LOG_FILE};
        bool isWork{0};
    private:
        int init();
        void proccess();
        void NewConnection();
        
        int ServSend(const int&, void*, unsigned int, int);
        int ServRecv(const int&, void*, unsigned int, int);
        
        int sendSuccess(const int&);
        int sendFail(const int&);
        int recvHead(const int&, Protocol::Head*);
        int recvMiddle(const int&, Protocol::Middle*);
        
        int endSesion(const int&);
        int chekConnection(const int&);
        int recvMsg(const int&, uint32_t);
        // int recvFile(const int&, uint64_t); // todo
    public:
        void start();
        void stop();
    public:
        bool isStarted();
        int GetStatus();  
        int getPort();
        std::string getIP();  
    private:
        uint64_t getTotalUseFilesSize();  // todo: rewrite
        int AddTotalUsedSize(uint64_t); // todo: rewrite
    public:
        Server(int, std::string);
        Server();
        ~Server();    
    };
} // namespace Net
#endif
