#include "server.h"

#define AND_WORK && isWork

namespace Net // class Server
{
    Server::~Server()
    {
        stop();
    }

    Server::Server(int port, std::string ip)
    :
    ServSock(-1),
    ServPort(port),
    ServStatus(0),
    ServIPAddr(ip),
    ServAddr{ 0 },
    ClientCounter(0),
    log("data/ServerLog"),
    clients(),
    isWork(0),
    DataFile(),
    ServAddrLenth(sizeof(ServAddr)),
    ServMaxClients(SERVER_MAX_CLIENTS_QUEUE)
    {}
    Server::Server()
    :
    ServSock(-1),
    ServPort(-1),
    ServStatus(0),
    ServIPAddr(),
    ServAddr{ 0 },
    ClientCounter(0),
    log("data/ServerLog"),
    clients(),
    isWork(0),
    DataFile(),
    ServAddrLenth(sizeof(ServAddr)),
    ServMaxClients(SERVER_MAX_CLIENTS_QUEUE)
    {}

    void Server::start()
    {
        if(isWork)
        {
            return;
        }
        init();

        isWork = 1;
        ServMaxClients = SERVER_MAX_CLIENTS_QUEUE;
        ProcessThread = std::thread([&]()
        {
            proccess();
        });
        log.log("Server started");
    }

    void Server::stop()
    {
        isWork = 0;
        ServMaxClients = 0;
        if(clients.empty())
        {
            return;
        }

        listen(ServSock, ServMaxClients);

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
                }));
            }
        }
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
        std::cout << "New message: ";// << std::string(msg) << std::endl;
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

    int Server::recvFile(const int& CltSock, uint64_t FileSize)
    {
        Protocol::Middle *middle = new Protocol::Middle();
        char *FileName, *buf = new char[FILE_BLOCK_SIZE];
        uint64_t it;

        if(FileSize == 0)
        {
            if(ServRecv(CltSock, &FileSize, 8, 0) < 0)
            {
                delete[] buf;
                delete middle;
                return -1;
            }
        }

        if(FileSize > FILE_MAX_SIZE || FileSize + getTotalUseFilesSize() > FILES_MAX_SUM_SIZE)
        {
            sendFail(CltSock);
            delete[] buf;
            delete middle;
            return -1;
        }

        it = (FileSize / FILE_BLOCK_SIZE);
        if(FILE_BLOCK_SIZE % FileSize > 0)
        {
            ++it;
        }
        
        if(recvMiddle(CltSock, middle) < 0)
        {
            delete[] buf;
            delete middle;
            return -1;
        }

        FileName = new char[middle->Data1];

        if(ServRecv(CltSock, FileName, middle->Data1, 0) < 0)
        {
            delete[] FileName;
            delete[] buf;
            delete middle;
            return -1;
        }

        for(int i = 0; i < it; i++)
        {
            if(ServRecv(CltSock, buf, FILE_BLOCK_SIZE, 0) < 0)
            {
                delete[] FileName;
                delete[] buf;
                delete middle;
                return -1;
            }

            // тут написать в логику для записи в файл
        }
        
        delete[] FileName;
        delete[] buf;
        delete middle;
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

    uint64_t Server::getTotalUseFilesSize()
    {
        if(!DataFile.is_open())
        {
            DataFile.open("data/ServerData", std::ios::in);
        }

        if(DataFile.tellg() <= 0)
        {
            return 0;
        }

        uint64_t size;

        mtxDataFile.lock();
        DataFile >> size;
        mtxDataFile.unlock();

        return size;
    }

    int Server::AddTotalUsedSize(uint64_t size)
    {
        if(!DataFile.is_open())
        {
            DataFile.open("data/ServerData", std::ios::ate); // now use std::ios::ate
        }

        mtxDataFile.lock();
        uint64_t size2;
        
        DataFile >> size2;
        DataFile << (size + size2);

        mtxDataFile.unlock();
        return 0;
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
