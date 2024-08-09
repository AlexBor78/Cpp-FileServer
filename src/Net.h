// Net.h
#pragma once

// STD
#include <cstdlib>
#include <cstdio>
#include <cmath>

// STL
#include <functional>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <mutex>

// sockets && inet
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <unistd.h>


namespace Net
{
    class Protocol;

    class Server; 
    class Client; 

    // class Buffer; 
    class File; 

    class Logger; 
} // namespace Net


#include "protocol.h"
#include "config.h"
#include "logger.h"
#include "server.h"
#include "client.h"

#define NET_H 1
