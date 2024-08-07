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
        try
        {
            sendHead(EndSesion);
            recvSuccess();       
        }
        catch(const char* e)
        {
            std::cout << e << std::endl;
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
        std::cout << "Trying to connect to server" << std::endl;
        ServAddr.sin_family = AF_INET;
        ServAddr.sin_port = htons(ServPort);
        ServAddr.sin_addr.s_addr = inet_addr(ServIP.c_str());

        if(connect_to_server(MySock, (sockaddr*)&ServAddr, AddrLenth) < 0)
        {
            Exit(3);
        }

        std::cout << "Connected to server" << std::endl;
        
        Status = 1;

        // Success connected to server
        // if(!chekConnection())
        // {
            // Exit(3);
        // }
        std::cout << "\nInited && connected success\n" << std::endl;
    }

    bool Client::chekConnection()
    {
        Protocol::Middle *answer = new Protocol::Middle();
        Protocol::Head *head = new Protocol::Head();
        head->Action = ChekConnect;
        int proccessed = 0;

        while (proccessed < Protocol::HeadSize)
        {
            proccessed = send_to_server(MySock, head, Protocol::HeadSize, 0);
            if(proccessed < 0)
            {
                return 0;
            }
        }

        proccessed = 0;

        while(proccessed < Protocol::MiddleSize)
        {
            proccessed = recv(MySock, answer, Protocol::MiddleSize, 0);
            if(proccessed < 0)
            {
                return 0;
            }
        }

        return answer->Status == SuccesAction;
        // you can write:
        return answer->Status; // it should work
    }

    int Client::sendHead(Net::Protocol::Head::ActionType action)
    {
        Protocol::Head *head = new Protocol::Head();
        int proccessed(0);

        head->Action = action;

        while(proccessed < Protocol::HeadSize)
        {
            proccessed = send_to_server(MySock, head, Protocol::HeadSize, 0);
            if(proccessed < 0)
            {
                throw("Couldn't send head");
            }
        }
        std::cout << "Head sended success" << std::endl;
        return 0;
    }

    int Client::sendHead(Net::Protocol::Head::ActionType action, uint32_t adddata)
    {
        Protocol::Head *head = new Protocol::Head();
        int proccessed(0);

        head->Action = action;
        head->AdditionalData = adddata;

        while(proccessed < Protocol::HeadSize)
        {
            proccessed = send_to_server(MySock, head, Protocol::HeadSize, 0);
            if(proccessed < 0)
            {
                throw("Couldn't send head");
            }
        }
        std::cout << "Head sended success" << std::endl;
        return 0;
    }

    bool Client::recvSuccess()
    {
        Protocol::Middle *close = new Protocol::Middle();
        int proccessed(0);

        while (proccessed < Protocol::MiddleSize)
        {
            proccessed = recv(MySock, close, Protocol::MiddleSize, 0);
            if(proccessed < 0)
            {
                return 0;
            }
        }

        std::cout << "End sended success" << std::endl;
        return close->Status;
    }

    std::string Client::send(const std::string& message)
    {
        std::string returning;
        int proccessed = 0, size = message.size();
        char *answer = new char[size];

        // send head: what server should doing
        sendHead(SendMessage, size);

        //send message
        proccessed = 0;
        while (proccessed < size)
        {
            proccessed = send_to_server(MySock, message.c_str(), size, 0);
            if(proccessed < 0)
            {
                throw("Message send error");
            }
        }

        std::cout << "Message sended sucess" << std::endl;
        
        // recv message
        proccessed = 0;
        while (proccessed < size)
        {
            proccessed = recv(MySock, answer, size, 0);
            if(proccessed < 0)
            {
                throw("Message recv error");
            }
        }

        std::cout << "Message recv-ed success" << std::endl;

        // converting char* to std::string
        for(int i=0; i < size; i++)
        {
            returning.push_back(answer[i]);
        }
        delete[] answer;

        std::cout << "End Opeation" << std::endl;
        recvSuccess();
        return returning;
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
