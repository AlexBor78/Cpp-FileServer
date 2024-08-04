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
    ServStatus(0),
    isWork(0)
    {}
    Server::Server()
    :
    ServPort(0),
    ServIPAddr(),
    ServAddr{ 0 },
    ServAddrLenth(sizeof(ServAddr)),
    ServSock(-1),
    ServStatus(0),
    isWork(0)
    {}

    void Server::start()
    {
        std::cout <<"void Server::start() started" << std::endl;
        init();

        isWork = 1;
        ProcessThread = std::thread([&]()
        {
            proccess();
        });

        std::cout <<"void Server::start() ended" << std::endl;
    }

    void Server::stop()
    {
        std::cout <<"void Server::stop() started" << std::endl;
        isWork = 0;
        if(ServStatus < 0)
        {
            return;
        }

        std::cout << "begin for" << std::endl;
        for(int i=0; i < clients.size(); i++)
        {
            clients.at(i).detach();
        }
        std::cout << "End for" <<std::endl;
        try
        {
            ProcessThread.join();
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << std::endl;
        }
        //catch()
        //{
        //    std::cerr << "error: unkknow error" << std::endl;
        //}
        
        std::cout <<"void Server::stop() ended" << std::endl;
    }

    void Server::proccess()
    {
        std::cout <<"void Server::proccess() started" << std::endl;

        std::cout << "listening will start" << std::endl;
        int counter = ClientCounter;
        listen(ServSock, 1);

        while(isWork)
        {
            if(counter < ClientCounter)
            {
                counter++;
                clients.push_back(std::thread([&]()
                {
                    char buf[1024];
                    if(accept(ServSock, (sockaddr*)&ServAddr, &ServAddrLenth) < 0)
                    {
                        throw("Couldn't accept connectoin");
                    }

                    Console.lock();
                    std::cout << "New Client" << std::endl;
                    Console.unlock();

                    mtxClientCounter.lock();
                    ClientCounter++;
                    mtxClientCounter.unlock();

                    std::cout << "recvfrom" << std::endl;
                    if(recvfrom(ServSock, buf, 1024, 0, (sockaddr*)&ServAddr, &ServAddrLenth) < 0)
                    {
                        throw("error to recv");
                    }

                    std::cout << "sendto" << std::endl;
                    if(sendto(ServSock, buf, 1024, 0, (sockaddr*)&ServAddr, ServAddrLenth) < 0)
                    {
                        throw("error to answer to client");
                    }

                }));
            }
        }

        for(int i=0; i < clients.size(); i++)
        {
            clients.at(i).detach();
        }
        std::cout <<"void Server::proccess() ended" << std::endl;
    }

    void Server::init()
    {
        std::cout <<"void Server::init() started" << std::endl;
        // test data to create socket
        if(ServPort<  0 || ServIPAddr.empty())
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

        std::cout << "Inited success" << std::endl;
        std::cout <<"void Server::init() ended" << std::endl;
    }

    bool Server::isStarted()
    {
        return ServStatus > 1;
    }

    void Server::Exit(int errcode, std::string err)
    {
        std::cout <<"void Server::Exit(int, std::string) started" << std::endl;
        Console.lock();
        std::cout << "SERVER FATAL ERROR: " << err << std::endl;
        std::cout<< "exit code: " << errcode <<std::endl;
        Console.unlock();

        stop();
        std::cout <<"void Server::Exit(int, std::string) will end next" << std::endl;
        exit(errcode);
    }
    
    void Server::Exit(int errcode)
    {
        std::cout <<"void Server::Exit(int) started" << std::endl;

        Console.lock();
        std::cout << "SERVER FATAL ERROR: " << GetErrorMessage(errcode) << std::endl;
        std::cout<< "exit code: " << errcode <<std::endl;
        Console.unlock();

        stop();
        std::cout <<"void Server::Exit(int) will end next" << std::endl;
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
         * 2 - listening
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

    std::string Server::GetErrorMessage(int errcode)
    {
    /*
    * 1 - "Invalid port or/and ip values";
    * 2 - "Couldn't create socket";
    * 3 - "Couldn't bind socket";
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
} // namespace Net
