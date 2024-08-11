#include "Net.h"

int main()
{
    Net::Client client(PORT, IP);
    std::string answer;
    client.connect();

#if CLIENT_AUTO_SEND_MESSAGE
    answer = client.send(CLIENT_MESSAGE);
#else
    std::string msg;

    std::cout << "Enter message to send" << std::endl;
    std::getline(std::cin, msg);

    answer = client.send(msg);
#endif
    std::cout << "Server answer: " << answer << std::endl;

    client.disconnect();
    std::cout << "Success end of programm" << std::endl;

    return 0;
}
