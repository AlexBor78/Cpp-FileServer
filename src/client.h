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
        int MySock{-1}, ServPort{-1};
        std::string ServIP{};
        sockaddr_in ServAddr{0};
        unsigned int AddrLenth{sizeof(ServAddr)};
        bool isconnected{0};
    private:
        void init();

        int CltSend(const int&, void*, unsigned int, int);
        int CltSend(const int&, const void*, unsigned int, int);
        int CltRecv(const int&, void*, unsigned int, int);

        int sendHead(const int&, Protocol::Head*);
        int sendHead(const int&, Protocol::Head::ActionType);
        int RecvSuccess(const int&);

        int chekConnection(const int&);
        int closeConnection(const int&);

    public:
        void connect();
        void disconnect();
        std::string send(const std::string&);
        //void send(Net::File);
        //void send()
    public:
        bool isConnected();
        // int GetStatus();
    public:
        Client(int, std::string);
        Client();
        ~Client();
    };
} // namespace Net
#endif
