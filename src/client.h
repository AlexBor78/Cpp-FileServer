// client.h
#include "Net.h"
#ifndef CLIENT_H
#define CLIENT_H 1

namespace
{
    auto connect_to_server = connect;
    auto send_to_server = send;
} // namespace

namespace Net
{
    class Client
    {
    private:
        int MySock, ServPort, Status;
        std::string ServIP;
        sockaddr_in ServAddr;
        unsigned int AddrLenth;
    private:
        void init();
    public:
        void connect();
        void disconnect();
        void send(std::string);
        //void send(Net::Data);
        //void send(Net::File);
        //void send()
    public:
        bool isConnected();
        int GetStatus();
        std::string answer();
        //Net::Server GetConnectedServer();
    private:
        void Exit(int, std::string);
        void Exit(int);
        void Exit();
        std::string GetErrorMessage(int);  
    public:
        Client(int, std::string);
        Client(Net::Server);
        Client();
        ~Client();
    };
} // namespace Net
#endif
