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
        bool isconnected;
    private:
        void init();

        int CltSend(const int&, void*, unsigned int, int);
        int CltSend(const int&, const void*, unsigned int, int);
        int CltRecv(const int&, void*, unsigned int, int);

        int sendHead(const int&, Protocol::Head*);
        int RecvSuccess(const int&);


    public:
        void connect();
        void disconnect();
        std::string send(const std::string&);
        //void send(Net::Data);
        //void send(Net::File);
        //void send()
    public:
        bool isConnected();
        int GetStatus();
    private:
        void Exit(int);
        std::string GetErrorMessage(int);  
    public:
        Client(int, std::string);
        Client();
        ~Client();
    };
} // namespace Net
#endif
