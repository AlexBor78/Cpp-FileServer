#include "Net.h"

int main()
{
    try
    {
        Net::Server server(PORT, IP);
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

        server.stop();
        
        std::cout << "Success end of programm" << std::endl;
    }
    catch(const std::system_error &e)
    {
        std::cerr << "Error: " << e.what() << '\n';
        std::cerr << "Exit code: " << e.code() << std::endl;
        std::cout << "Unsuccess end of programm" << std::endl;
    }
    
    return 0;
}
