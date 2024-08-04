#include "Net.h"

int main()
{
    Net::Client client(1456, "192.168.124.181");

    client.connect();
    if(!client.isConnected())
    {
        std::cerr << "Couldn't connect to server";
        exit(1);
    }

    client.send("hello!");

    return 0;
}
