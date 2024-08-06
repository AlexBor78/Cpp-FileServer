#include "Net.h"

int main()
{
    Net::Server server(5554, "127.0.0.2");
    server.start();

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
    
    std::cout << "Success end of programm" << std::endl;
    return 0;
}
