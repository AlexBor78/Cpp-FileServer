#include "client.h"

namespace Net
{
    Client::~Client()
    {
        disconnect();
    }

    Client::Client(int port, std::string ip)
    :
    MySock(-1),
    ServPort(port),
    Status(0),
    ServIP(ip),
    ServAddr{ 0 },
    AddrLenth(sizeof(ServAddr))
    {}
    Client::Client()
    :
    MySock(-1),
    ServPort(-1),
    Status(0),
    ServIP(),
    ServAddr{ 0 },
    AddrLenth(sizeof(ServAddr))
    {}

    void Client::connect()
    {
        init();
        isconnected = 1;
    }

    void Client::disconnect()
    {
        if(isconnected == 0)
        {
            return;
        }

        
        close(MySock);
    }

    void Client::init()
    {
        // check values for invalid
        if(ServPort < 0 || ServIP.empty())
        {
            Exit(1);
        }

        // creating socket
        MySock = socket(AF_INET, SOCK_STREAM, 0);
        if(MySock < 0)
        {
            Exit(2);
        }

        // connect to server
        // std::cout << "Trying to connect to server" << std::endl;
        ServAddr.sin_family = AF_INET;
        ServAddr.sin_port = htons(ServPort);
        ServAddr.sin_addr.s_addr = inet_addr(ServIP.c_str());

        if(connect_to_server(MySock, (sockaddr*)&ServAddr, AddrLenth) < 0)
        {
            Exit(3);
        }

        // std::cout << "Connected to server" << std::endl;
        
        Status = 1;

        std::cout << "\nInited && connected success\n" << std::endl;
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
        if(CltSend(ServSock, head, Protocol::HeadSize, 0) < 0)
        {
            return -1;
        }
        return 0;
    }

    int Client::RecvSuccess(const int& ServSock)
    {
        Protocol::Middle *succ = new Protocol::Middle();
        if(CltRecv(ServSock, succ, Protocol::MiddleSize, 0) < 0)
        {
            return -1;
        }
        int answer = succ->Status == SuccesAction;
        delete succ;
        return answer - 1;
    }

    std::string Client::send(const std::string& message)
    {
        if(message.size() > pow(2, 32))
        {
            throw("Message is to big");
        }

        char *answerbuf = new char[message.size()];
        std::string answer;
        Protocol::Head *head = new Protocol::Head();
        int size = message.size();

        head->Action = SendMessage;
        head->AdditionalData = message.size();

        // send head
        if(sendHead(MySock, head) < 0)
        {
            throw("Send head error");
        }
        
        // send message
        if(CltSend(MySock, message.c_str(), size, 0) < 0)
        {
            throw("Send message error");
        }

        // recv message
        if(CltRecv(MySock, answerbuf, size, 0) < 0)
        {
            throw("Recv message error");
        }

        if(RecvSuccess(MySock) < 0)
        {
            throw("End error");
        }

        for(int i=0; i < size; i++)
        {
            answer.push_back(answerbuf[i]);
        }
        
        delete[] answerbuf;
        return answer;
    }

    bool Client::isConnected()
    {
        return Status > 0;
    }

    int Client::GetStatus()
    {
        /**
         * 0 - created
         * 1 - connected to server
         * 2 - sending to server
         * 
         */
        return Status;
    }

    void Client::Exit(int errcode)
    {
        std::cout << "Client fatal error: " << GetErrorMessage(errcode) << std::endl;
        std::cout<< "exit code: " << errcode <<std::endl;

        disconnect();
        exit(errcode);
    }

    std::string Client::GetErrorMessage(int errcode)
    {
        /**
         * 1 - "Invalid port or/and ip values";
         * 2- "Couldn't create socket";
         * 3 - "Couldn't connect to server";
         * 4 - "Faild to send to server";
         * 
         */

        switch (errcode)
        {
        case(1):
            return "Invalid port or/and IP values";
            break;
        case(2):
            return "Couldn't create socket";
            break;
        case(3):
            return "Couldn't connect to server";
            break;
        case(4):
            return "Faild to send to server";
            break;

        
        default:
            break;
        }
        return "Trolololo";
    }

} // namespace Net
