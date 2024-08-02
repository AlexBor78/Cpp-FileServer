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
    Client::Client(Net::Server srv)
    :
    MySock(-1),
    ServPort(srv.getPort()),
    Status(0),
    ServIP(srv.getIP()),
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
    }

    void Client::disconnect()
    {
        
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
        ServAddr.sin_family = AF_INET;
        ServAddr.sin_port = htons(ServPort);
        ServAddr.sin_addr.s_addr = inet_addr(ServIP.c_str());

        if(connect_to_server(MySock, (sockaddr*)&ServAddr, AddrLenth) < 0)
        {
            Exit(3);
        }
        

        // Success connected to server
    }

    void Client::send(std::string message)
    {
        Status = 2;
        if(send_to_server(MySock, message.c_str(), message.size(), 0) < 0)
        {
            Exit(4);
        }
        Status = 1;
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

    void Client::Exit(int errcode, std::string err)
    {
        std::cout << "Client fatal error: " << err << std::endl;
        std::cout<< "exit code: " << errcode <<std::endl;

        disconnect();
        exit(errcode);
    }
    void Client::Exit(int errcode)
    {
        std::cout << "Client fatal error: " << GetErrorMessage(errcode) << std::endl;
        std::cout<< "exit code: " << errcode <<std::endl;

        disconnect();
        exit(errcode);
    }
    void Client::Exit()
    {
        std::cout << "Client fatal error: unknow error" << std::endl;
        std::cout<< "unknow exit code" <<std::endl;

        disconnect();
        exit(-1);
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
