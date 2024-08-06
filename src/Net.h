// Net.h
#pragma once
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <thread>
#include <mutex>
#include <chrono>
#include <cmath>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

namespace Net
{
    class Protocol;
    class Server; // done
    class Client; // done
    
    class Buffer; // done
    class File; // done
    //class Data; // done

    //class Error; // trash // don't use
    //class Logger; // done redefinition or incomplet, what the fuck?
} // namespace Net

//#include "buffer.h"
// #include "data.h"
#include "protocol.h"
#include "server.h"
#include "client.h"

#define NET_H 1
