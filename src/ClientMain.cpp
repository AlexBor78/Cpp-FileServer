#include "Net.h"

int main()
{
    //Net::Client client(3243, "192.168.124.181");
    Net::Client client(5454, "127.0.0.2");
    std::string msg;
    
    client.connect();
    //client.send("Hey");

    std::cout << "Enter message to send" << std::endl;
    std::getline(std::cin, msg);
    
    std::cout << "Sending to server..." << std::endl;
    client.send(msg);
    std::cout << "Sended success" << std::endl;
    
    std::cout << "Trying to recv answer from server" << std::endl;
    std::string answer = client.answer();
    std::cout << "Server answer: " << answer << std::endl;

    std::cout << std::endl;

    std::cout << "Success end of programm" << std::endl;
    return 0;
}
