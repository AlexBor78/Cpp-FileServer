// Net.h
#pragma once
#include <stdlib.h>
#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <chrono>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

namespace Net
{
    class Server;
    class Client;
    
    class File;
    class Data;
} // namespace Net

#include "server.h"
#include "client.h"
#include "data.h"
#include "file.h"

#define NET_H 1
