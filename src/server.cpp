#include "server.h"

#define WORK && isWork
#define SERVER_MAX_CLIENT 5

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
    ServMaxClients(SERVER_MAX_CLIENT),
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
    ServMaxClients(SERVER_MAX_CLIENT),
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
        if(clients.empty())
        {
            return;
        }

        for(int i=0; i < clients.size(); i++)
        {
            std::cout << "Joing: " << i << std::endl;
            clients.at(i).detach(); // error here
        }

        ProcessThread.join();
    }

    void Server::proccess()
    {
        std::cout << "Listening for new connections..." << std::endl;

        clients.clear();
        ClientCounter = 0;
        int counter = 0;

        listen(ServSock, ServMaxClients);

        while(isWork)
        {
            if(counter <= ClientCounter)
            {
                ++counter;
                clients.push_back(std::thread([&]()
                {
                    int CltSock = accept(ServSock, 0, 0);
                    if(CltSock < 0)
                    {
                        throw("Couldn't accept new connection");
                    }

                    Console.lock();
                    std::cout << "\nNew connection\n" << std::endl;
                    Console.unlock();
                    mtxClientCounter.lock();
                    ++ClientCounter;
                    mtxClientCounter.unlock();

                    bool ConnectoinOpen = 1;
                    Protocol::Head *head;

                    while (ConnectoinOpen WORK) 
                    {
                        if(!isWork)
                        {
                            ConnectoinOpen = 0;
                        }

                        head = new Protocol::Head();
                        if(recvHead(CltSock, head) < 0)
                        {
                            Console.lock();
                            std::cerr << "Coulnd't recv Protocol::Head" << std::endl;
                            Console.unlock();
                            return;
                        }

                        switch (head->Action)
                        {
                        case(ChekConnect):
                            if(chekConnection(CltSock) < 0)
                            {
                                Console.lock();
                                std::cerr << "Coulnd't check connection" << std::endl;
                                Console.unlock();
                                return;
                            } break;
                        case(SendMessage):
                            if(recvMsg(CltSock, head->AdditionalData) < 0)
                            {
                                Console.lock();
                                std::cerr << "Coulnd't recv message" << std::endl;
                                Console.unlock();
                                return;
                            } break;
                        case(EndSesion):
                            if(sendSuccess(CltSock) < 0)
                            {
                                Console.lock();
                                std::cerr << "Coulnd't close sesion" << std::endl;
                                Console.unlock();
                                return;
                            }
                            ConnectoinOpen = 0;
                            break;
                        default:
                            Console.lock();
                            std::cerr << "Unknow Action" << std::endl;
                            Console.unlock();
                            if(sendFail(CltSock) < 0)
                            {
                                Console.lock();
                                std::cerr << "Coldn't send Fail" << std::endl;
                                Console.unlock();
                            }
                            return;
                            break;
                        }
                        delete head; // witout this line will mem leak
                        std::cout << "End of operation " << std::endl;
                    }
                    close(CltSock);
                    Console.lock();
                    std::cout << "Connection closed success\n" << std::endl;
                    Console.unlock();
                }));
            }
        }
    }

    int Server::ServSend(const int &CltSock, void *buf, unsigned int size, int flags)
    {
        int proccessed(0);
        while(proccessed < size WORK)
        {
            proccessed = send(CltSock, buf + proccessed, size - proccessed, flags);
            if(proccessed < 0)
            {
                return -1;
            }
        }
        return 0;
    }

    int Server::ServRecv(const int& CltSock, void *buf, unsigned int size, int flags)
    {
        int proccessed(0);
        while(proccessed  < size WORK)
        {
            proccessed = recv(CltSock, buf + proccessed, size - proccessed, flags);
            if(proccessed  < 0)
            {
                return -1;
            }
        }
        return 0;
    }

    int Server::sendSuccess(const int& CltSock)
    {
        Protocol::Middle *answer = new Protocol::Middle();
        answer->Status = SuccesAction;

        if(ServSend(CltSock, answer, Protocol::MiddleSize, 0) < 0)
        {
            return -1;
        }   
        delete answer;
        return 0;  
    }

    int Server::sendFail(const int& CltSock)
    {
        Protocol::Middle *answer = new Protocol::Middle();
        answer->Status = FaildAction;

        if(ServSend(CltSock, answer, Protocol::MiddleSize, 0) < 0)
        {
            return -1;
        }
        delete answer;
        return 0;  
    }

    int Server::recvHead(const int &CltSock, Protocol::Head* head)
    {
        if(ServRecv(CltSock, head, Protocol::HeadSize, 0) < 0)
        {
            return -1;
        }
        return 0;        
    }

    int Server::chekConnection(const int& CltSock)
    {
        Protocol::Middle *answer = new Protocol::Middle();
        answer->Status = SuccesAction;
        
        if(ServSend(CltSock, answer, Protocol::MiddleSize, 0) < 0)
        {
            return -1;
        }
        delete answer;
        return 0;
    }

    int Server::recvMsg(const int& CltSock, uint32_t size)
    {
        char *msg = new char[size];

        if(ServRecv(CltSock, msg, size, 0) < 0)
        {
            return -1;
        }

        Console.lock();
        std::cout << "New message:" << std::string(msg) << std::endl;
        Console.unlock();

        if(ServSend(CltSock, msg, size, 0) < 0)
        {
            return -1;
        }    

        delete[] msg;

        if(sendSuccess(CltSock) < 0)
        {
            return -1;
        }
        return 0;
    }

    void Server::init()
    {
        // test data to create socket
        if(ServPort < 0 || ServIPAddr.empty())
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

    void Server::Exit(int errcode)
    {
        Console.lock();
        std::cout << "SERVER FATAL ERROR: " << GetErrorMessage(errcode) << std::endl;
        std::cout<< "exit code: " << errcode <<std::endl;
        Console.unlock();

        stop();
        exit(errcode);
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
