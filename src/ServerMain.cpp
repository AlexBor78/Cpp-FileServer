#include "Net.h"

int main()
{

    //Net::Server server(35643, "192.168.124.181");
    Net::Server server(5454, "127.0.0.2");
    server.start();
    //std::this_thread::sleep_for(std::chrono::milliseconds(1000)); // 1s
    //server.stop();

    std::cout << "Server started" << std::endl;
    std::string enter;

    while (1)
    {
        std::cout << "Enter \"stop\" when you want to stop server" << std::endl;
        std::getline(std::cin, enter);
        if(enter == "stop")
        {
            break;
        }
    }
    
    std::cout << "Success" << std::endl;
    return 0;
}
