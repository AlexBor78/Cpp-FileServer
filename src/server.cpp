#include "server.h"

#define AND_WORK && isWork

namespace Net // class Server
{
    Server::~Server()
    {
        stop();
    }

    Server::Server() = default;
    Server::Server(int port, std::string ip)
    :
    ServPort(port),
    ServIPAddr(ip)
    {}

    void Server::start()
    {
        if(isWork)
        {
            return;
        }
        init();

        isWork = 1;
        ServMaxQueue = SERVER_MAX_CLIENTS_QUEUE;
        ProcessThread = std::thread([&]()
        {
            proccess();
        });
        log.log("Server started");
    }

    void Server::stop()
    {
        isWork = 0;
        ServMaxQueue = 0;
        if(clients.empty())
        {
            return;
        }

        listen(ServSock, ServMaxQueue);

        for(int i = 0; i < clients.size() - 1; i++)
        {
            clients.at(i).join();
        }

        shutdown(ServSock, 2);
        clients.back().join(); // join accept-connection thread
        close(ServSock);

        ProcessThread.join();
        log.log("Server stoped");
    }

    void Server::proccess()
    {
        std::cout << "Listening for new connections..." << std::endl;
        log.log("Listening started");

        clients.clear();
        ClientCounter = 0;
        int counter = 0;

        listen(ServSock, ServMaxQueue);

        while(isWork)
        {
            if(counter <= ClientCounter)
            {
                ++counter;
                clients.push_back(std::thread([&]()
                {
                    NewConnection();
                }));
            }
        }
    }

    void Server::NewConnection()
    {
        int CltSock = accept(ServSock, 0, 0);
        if(CltSock < 0)
        {
            if(isWork)
            { 
                std::cout << "Couldn't accept new connection" << std::endl;
                return;
            }

            close(CltSock);

            Console.lock();
            std::cout << "Socket closed success\n" << std::endl;
            Console.unlock();

            return;
        }

        log.log("New connection");
        Console.lock();
        std::cout << "\nNew connection\n" << std::endl;
        Console.unlock();

        mtxClientCounter.lock();
        ++ClientCounter;
        mtxClientCounter.unlock();

        bool ConnectoinOpen = 1;
        Protocol::Head *head;

        while (ConnectoinOpen AND_WORK) 
        {
            head = new Protocol::Head();
            if(recvHead(CltSock, head) < 0)
            {
                Console.lock();
                std::cerr << "Coulnd't recv Protocol::Head" << std::endl;
                Console.unlock();
            }

            switch (head->Action)
            {
            case(ChekConnect):
                log.log("ChekConnection");
                if(chekConnection(CltSock) < 0)
                {
                    Console.lock();
                    std::cerr << "Coulnd't check connection" << std::endl;
                    Console.unlock();
                } break;
            case(SendMessage):
                log.log("SendMessage");
                if(recvMsg(CltSock, head->AdditionalData) < 0)
                {
                    Console.lock();
                    std::cerr << "Coulnd't recv message" << std::endl;
                    Console.unlock();
                } break;
            case(EndSesion):
                ConnectoinOpen = 0;
                log.log("EndSesion");
                if(endSesion(CltSock) < 0)
                {
                    Console.lock();
                    std::cerr << "Coulnd't close sesion" << std::endl;
                    Console.unlock();
                } break;
            case(NotinhToDo):
                break;
            case(SendFile):
                sendFail(CltSock);
                break;
            default:
                if(isWork)
                {
                    Console.lock();
                    std::cerr << "Unknow Action" << std::endl;
                    Console.unlock();
                    log.log("Unknow Action");
                    if(sendFail(CltSock) < 0)
                    {
                        Console.lock();
                        std::cerr << "Coldn't send Fail" << std::endl;
                        Console.unlock();
                    }
                } break;
            }
            delete head; // witout this line will mem leak
            log.log("End of operation");
        }
        close(CltSock);
        log.log("Connection closed");
        
        Console.lock();
        std::cout << "Connection closed success\n" << std::endl;
        Console.unlock();
    }

    int Server::ServSend(const int &CltSock, void *buf, unsigned int size, int flags)
    {
        int proccessed(0);
        while(proccessed < size AND_WORK)
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
        while(proccessed  < size AND_WORK)
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
        Protocol::End *answer = new Protocol::End(SuccesAction);
        int ret = ServSend(CltSock, answer, Protocol::EndSize, 0);
        delete answer;
        return ret;  
    }

    int Server::sendFail(const int& CltSock)
    {
        Protocol::End *answer = new Protocol::End(FaildAction);
        int ret = ServSend(CltSock, answer, Protocol::EndSize, 0);
        delete answer;
        return ret;
    }

    int Server::recvHead(const int &CltSock, Protocol::Head* head)
    {
        return ServRecv(CltSock, head, Protocol::HeadSize, 0);        
    }

    int Server::recvMiddle(const int& CltSock, Protocol::Middle* middle)
    {
        return ServRecv(CltSock, middle, Protocol::MiddleSize, 0);
    }

    int Server::endSesion(const int& CltSock)
    {
        return sendSuccess(CltSock);
    }

    int Server::chekConnection(const int& CltSock)
    {
        return sendSuccess(CltSock);
    }

    int Server::recvMsg(const int& CltSock, uint32_t size)
    {
        char *msg = new char[size];

        // recv message
        if(ServRecv(CltSock, msg, size, 0) < 0)
        {
            return -1;
        }

        Console.lock();
        std::cout << "New message: ";
        for(int i=0;i < size; i++)
        {
            std::cout << msg[i];
        }
        std::cout << std::endl;
        Console.unlock();

        // send message
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

    int Server::init()
    {
        // test data to create socket
        if(ServPort < 0 || ServIPAddr.empty())
        {
            std::cerr << "Invalid ip or port value" << std::endl;
            return -1;
        }

        // create socket
        ServSock = socket(AF_INET, SOCK_STREAM, 0);
        if(ServSock < 0)
        {
            std::cerr << "Couldn't create socket" << std::endl;
            return -1;
        }

        // binding socket
        ServAddr.sin_family = AF_INET;
        ServAddr.sin_port = htons(ServPort);
        ServAddr.sin_addr.s_addr = inet_addr(ServIPAddr.c_str());

        if(bind(ServSock, (sockaddr*)&ServAddr, ServAddrLenth) < 0)
        {
            std::cerr << "Couldn't bind socket" << std::endl;
            return -1;
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
