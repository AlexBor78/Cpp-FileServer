// Net.h
#pragma once
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
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
    
    class Buffer;
    class File;
    class Data;
    class Error;
} // namespace Net

#include "server.h"
#include "client.h"
#include "data.h"
#include "file.h"
#include "buffer.h"
#include "error.h"

#define NET_H 1
