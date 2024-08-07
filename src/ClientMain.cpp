#include "Net.h"

int main()
{
    //Net::Client client(3243, "192.168.124.181");
    Net::Client client(PORT, IP);
    std::string msg;
    
    client.connect();
    std::string answ = client.send("Hey");
    std::cout << "Server answer: " << answ << std::endl;

    //std::cout << "Enter message to send" << std::endl;
    //std::getline(std::cin, msg);

    std::cout << "Success end of programm" << std::endl;
    return 0;
}

/*
fix some bugs
write some functions to easer developing int future
*/