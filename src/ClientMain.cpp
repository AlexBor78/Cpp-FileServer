#include "Net.h"

int main()
{
    Net::Client client(PORT, IP);
    std::string msg;
    
    client.connect();

    std::cout << "Enter message to send" << std::endl;
    std::getline(std::cin, msg);

    std::string answ = client.send(msg);
    std::cout << "Server answer: " << answ << std::endl;


    std::cout << "Success end of programm" << std::endl;
    return 0;
}
