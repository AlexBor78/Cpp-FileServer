#include "client.h"

namespace Net
{
    Client::~Client()
    {
        disconnect();
    }

    Client::Client() = default;
    Client::Client(int port, std::string ip)
    :
    ServPort(port),
    ServIP(ip)
    {}

    void Client::connect()
    {
        if(isconnected)
        {
            return;
        }
        init();
    }

    void Client::disconnect()
    {
        if(!isconnected)
        {
            return;
        }

        // из-за этого происходит неправильное закрытие \/
        if(closeConnection(MySock) < 0)
        {
            std::cerr << "Couldn't close connection" << std::endl;
            // throw("Couldn't close connection"); // can be in destructor
        }

        close(MySock);
    }

    int Client::CltSend(const int &ServSock, void *buf, unsigned int size, int flags)
    {
        int proccessed(0);
        while(proccessed < size)
        {
            proccessed = send_to_server(ServSock, buf + proccessed, size - proccessed, flags);
            if(proccessed < 0)
            {
                return -1;
            }
        }
        return 0;
    }
    int Client::CltSend(const int &ServSock, const void *buf, unsigned int size, int flags)
    {
        int proccessed(0);
        while(proccessed < size)
        {
            proccessed = send_to_server(ServSock, buf + proccessed, size - proccessed, flags);
            if(proccessed < 0)
            {
                return -1;
            }
        }
        return 0;
    }

    int Client::CltRecv(const int &ServSock, void *buf, unsigned int size, int flags)
    {
        int proccessed(0);
        while(proccessed  < size)
        {
            proccessed = recv(ServSock, buf + proccessed, size - proccessed, flags);
            if(proccessed  < 0)
            {
                return -1;
            }
        }
        return 0;
    }

    int Client::sendHead(const int &ServSock, Protocol::Head* head)
    {
        return CltSend(ServSock, head, Protocol::HeadSize, 0);
    }
    int Client::sendHead(const int& ServSock, Protocol::Head::ActionType act)
    {
        Protocol::Head *head = new Protocol::Head(act);
        if(CltSend(ServSock, head, Protocol::HeadSize, 0) < 0)
        {
            delete head;
            return -1;
        }
        delete head;
        return 0;
    }

    int Client::RecvSuccess(const int& ServSock)
    {
        Protocol::End *succ = new Protocol::End();
        if(CltRecv(ServSock, succ, Protocol::EndSize, 0) < 0)
        {
            delete succ;
            return -1;
        }
        int answer = succ->Status == SuccesAction;
        delete succ;
        return answer - 1;
    }

    int Client::chekConnection(const int& ServSock)
    {
        if(sendHead(ServSock, ChekConnect) < 0)
        {
            return -1;
        }
        return RecvSuccess(ServSock);
    }

    int Client::closeConnection(const int& ServSock)
    {
        if(sendHead(ServSock, EndSesion) < 0)
        {
            std::cerr << "\"EndSesion Head\" send error" << std::endl;
            return -1;
        }

        if(RecvSuccess(ServSock) < 0)
        {
            std::cerr << "Recv error" << std::endl;
            return -1;
        }

        return 0;
        // return RecvSuccess(ServSock);
    }

    std::string Client::send(const std::string& message)
    {
        // chek values to invalid
        if(message.size() > pow(2, 32))
        {
            throw("Message is to big");
        }

        // definitoin
        char *answerbuf;
        std::string answer;
        int size = message.size();
        Protocol::Head *head = new Protocol::Head(SendMessage, size);

        // send head
        if(sendHead(MySock, head) < 0)
        {
            delete head;
            throw("Send head error");
        }
        delete head;
        
        // send message
        if(CltSend(MySock, message.c_str(), size, 0) < 0)
        {
            throw("Send message error");
        }

        // recv message
        answerbuf = new char[size];
        if(CltRecv(MySock, answerbuf, size, 0) < 0)
        {
            delete[] answerbuf;
            throw("Recv message error");
        }

        if(RecvSuccess(MySock) < 0)
        {
            delete[] answerbuf;
            throw("End error");
        }

        for(int i=0; i < size; i++)
        {
            answer.push_back(answerbuf[i]);
        }
        
        delete[] answerbuf;
        return answer;
    }

    void Client::init()
    {
        // check values for invalid
        if(ServPort < 0 || ServIP.empty())
        {
            throw("Invalid port or ip value");
        }

        // creating socket
        MySock = socket(AF_INET, SOCK_STREAM, 0);
        if(MySock < 0)
        {
            throw("Couldn't create socket");
        }

        // connect to server
        ServAddr.sin_family = AF_INET;
        ServAddr.sin_port = htons(ServPort);
        ServAddr.sin_addr.s_addr = inet_addr(ServIP.c_str());

        if(connect_to_server(MySock, (sockaddr*)&ServAddr, AddrLenth) < 0)
        {
            throw("Couldn't connectn to server");
        }

        if(chekConnection(MySock) < 0)
        {
            throw("Couldn't chek connection to server");
        }

        isconnected = 1;

        std::cout << "\nInited && connected success\n" << std::endl;
    }

    bool Client::isConnected()
    {
        return isconnected;
    }

} // namespace Net
