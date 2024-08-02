#include "server.h"

namespace Net
{
    Server::~Server()
    {
        stop();
    }

    Server::Server(int port, std::string ip)
    :
    ServPort(port),
    ServIPAddr(ip),
    ServAddr{ 0 },
    ServAddrLenth(sizeof(ServAddr)),
    ServSock(-1),
    ServStatus(0)
    {}
    Server::Server()
    :
    ServPort(0),
    ServIPAddr(),
    ServAddr{ 0 },
    ServAddrLenth(sizeof(ServAddr)),
    ServSock(-1),
    ServStatus(0)
    {}

    void Server::start()
    {
        init();

        //ServProccess = std::thread(proccess); // server started

    }

    void Server::stop()
    {
        if(ServStatus < 0)
        {
            return;
        }


    }

    void Server::proccess()
    {
        listen(ServSock, 1);

    }

    void Server::init()
    {
        // test data to create socket
        if(ServSock <  0 || ServIPAddr.empty())
        {
            Exit(1);
        }

        // create socket
        ServSock = socket(AF_INET, SOCK_STREAM, 0);
        if(ServSock < 0)
        {
            Exit(2);
        }

        // binding socket
        ServAddr.sin_family = AF_INET;
        ServAddr.sin_port = htons(ServPort);
        ServAddr.sin_addr.s_addr = inet_addr(ServIPAddr.c_str());

        if(bind(ServSock, (sockaddr*)&ServAddr, ServAddrLenth) < 0)
        {
            Exit(3);
        }

        ServStatus = 1;
    }

    bool Server::isStarted()
    {
        return ServStatus > 1;
    }

    void Server::Exit(int errcode, std::string err)
    {
        Console.lock();
        std::cout << "SERVER FATAL ERROR: " << err << std::endl;
        std::cout<< "exit code: " << errcode <<std::endl;
        Console.unlock();

        stop();
        exit(errcode);
    }
    
    void Server::Exit(int errcode)
    {
        Console.lock();
        std::cout << "SERVER FATAL ERROR: " << GetErrorMessage(errcode) << std::endl;
        std::cout<< "exit code: " << errcode <<std::endl;
        Console.unlock();

        stop();
        exit(errcode);
    }

    void Server::Exit()
    {
        Console.lock();
        std::cout << "SERVER FATAL ERROR: unknow error" << std::endl;
        std::cout<< "unknow exit code" <<std::endl;
        Console.unlock();

        stop();
        exit(-1);
    }

    int Server::GetStatus()
    {
        /* 
         * 0 - created
         * 1 - inited
         * 2 - started(working)
         * 3 - listening
         * 
         */
        return ServStatus;
        
    }

    int Server::getPort()
    {
        return ServPort;
    }

    std::string Server::getIP()
    {
        return ServIPAddr;
    }

} // namespace Net

std::string Net::Server::GetErrorMessage(int errcode)
{
/*
 * 1 - "Invalid port or/and ip values";
 * 2 - "Couldn't create socket";
 * 3 - "Couldn't bind socket";
 * 
 * 
 * 
 * 
 * 
*/

    switch (errcode)
    {
    case(1):
        return "Invalid port or/and ip values";
        break;
        
    case(2):
        return "Couldn't create socket";
        break;

    case(3):
        return "Couldn't bind socket";
        break;

    default:
        return "unknow error";
        break;
    }

    return "trololololo";
}