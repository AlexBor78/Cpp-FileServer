// Net.h
#pragma once
#include "config.h"

// STD
#include <cstdlib>
#include <cstdio>

// STL
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <thread>
#include <mutex>
#include <chrono>
#include <cmath>

// sockets && inet
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

    class Logger; // done redefinition or incomplet, what the fuck?
    //class Error; // trash // don't use
} // namespace Net

//#include "buffer.h"
// #include "data.h"
#include "logger.h"
#include "protocol.h"
#include "server.h"
#include "client.h"

#define NET_H 1
