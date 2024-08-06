#include "server.h"

#define WORK && isWork

namespace Net // class Server
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
    ClientCounter(0),
    ServStatus(0),
    ServMaxClients(5),
    isWork(0)
    {}
    Server::Server()
    :
    ServPort(0),
    ServIPAddr(),
    ServAddr{ 0 },
    ServAddrLenth(sizeof(ServAddr)),
    ServSock(-1),
    ClientCounter(0),
    ServStatus(0),
    ServMaxClients(5),
    isWork(0)
    {}

    void Server::start()
    {
        if(isWork)
        {
            return;
        }
        init();

        isWork = 1;
        ProcessThread = std::thread([&]()
        {
            proccess();
        });
    }

    void Server::stop()
    {
        isWork = 0;
        if(ServStatus < 0)
        {
            return;
        }

        for(int i=0; i < clients.size(); i++)
        {
            clients.at(i).detach();
        }
        
        ProcessThread.join();
    }

    void Server::proccess()
    {
        std::cout << "Listening for new connections..." << std::endl;
        int counter = 0;
        listen(ServSock, ServMaxClients);

        while(isWork)
        {
            if(counter <= ClientCounter)
            {
                ++counter;
                clients.push_back(std::thread([&]()
                {
                    int CltSock = accept(ServSock, (sockaddr*)&ServAddr, &ServAddrLenth);
                    if(CltSock < 0)
                    {
                        throw("Couldn't accept new connection");
                    }

                    Console.lock();
                    std::cout << "New connection" << std::endl;
                    Console.unlock();

                    bool ConnectoinOpen = 1;
                    int proccessed = 0;
                    Protocol::Head *head = new Protocol::Head();

                    while (ConnectoinOpen WORK) 
                    {
                        proccessed = 0;
                        while (proccessed < Protocol::HeadSize WORK)
                        {
                            proccessed = recv(CltSock, head, Protocol::HeadSize, 0);
                            // if(proccessed < 0)
                            // {
                                // std::cout << "noting to recv" << std::endl;
                                // throw(1);
                            // }
                        }

                        switch (head->Action)
                        {
                        case(ChekConnect):
                            chekConnection(CltSock);
                            break;
                        case(SendMessage):
                            recvMsg(CltSock, head->AdditionalData);
                            break;
                        case(EndSesion):
                            sendSuccess(CltSock);
                            ConnectoinOpen = 0;
                            break;
                        default:
                            break;
                        }
                    }
                    close(CltSock);
                    Console.lock();
                    std::cout << "Connection closed success" << std::endl;
                    Console.unlock();
                }));
            }
        }
    }

    int Server::sendSuccess(const int& CltSock)
    {
        int proccessed = 0;
        Protocol::Middle *answer = new Protocol::Middle();
        answer->Status = SuccesAction;

        std::cout << "starting answering" << std::endl;
        
        while (proccessed < Protocol::MiddleSize WORK)
        {
            proccessed = send(CltSock, answer, Protocol::MiddleSize, 0);
            if(proccessed < 0)
            {
                std::cout << "Error" << std::endl;
                throw("\"Succcess answering\" error");
            }
        }    
        return 0;  
    }

    int Server::chekConnection(const int& CltSock)
    {
        std::cout << "Chek connection" << std::endl;
        int proccessed = 0;
        Protocol::Middle *answer = new Protocol::Middle();
        answer->Status = SuccesAction;
        
        while (proccessed < 0 WORK)
        {
            proccessed = send(CltSock, answer, Protocol::MiddleSize, 0);
            if(proccessed < 0)
            {
                throw("chek connection error");
            }
        }        
        return 0;
    }

    int Server::recvMsg(const int& CltSock, uint32_t size)
    {
        char *msg = new char[size];
        int proccessed = 0;

        while(proccessed < size)
        {
            proccessed = recv(CltSock, msg, size, 0);
            if(proccessed < 0)
            {
                throw("Message recv error");
            }
        }

        Console.lock();
        std::cout << "New message:" << std::string(msg) << std::endl;
        Console.unlock();

        proccessed = 0;

        std::cout << "returning message..." << std::endl;

        while (proccessed < size)
        {
            proccessed = send(CltSock, msg, size, 0);
            if(proccessed < 0)
            {
                throw("send error");
            }
        }      

        std::cout << "Message was return" << std::endl;

        sendSuccess(CltSock);
        delete[] msg;
        return 0;
    }

    void Server::init()
    {
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
    }

    bool Server::isStarted()
    {
        return isWork;
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
