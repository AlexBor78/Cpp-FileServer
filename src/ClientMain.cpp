#include "Net.h"

int main()
{
    Net::Client client(PORT, IP);
    std::string msg;
    std::string answer;

    client.connect();

    std::cout << "Enter message to send" << std::endl;
    std::getline(std::cin, msg);

    answer = client.send(msg);
    std::cout << "Server answer: " << answer << std::endl;

    client.disconnect();
    std::cout << "Success end of programm" << std::endl;
    return 0;
}
