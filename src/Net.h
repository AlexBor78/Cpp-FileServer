// Net.h
#pragma once
// #undef LOGGGER_H
#include "config.h"
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

#include "logger.h"

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
#include "protocol.h"
#include "server.h"
#include "client.h"

#define NET_H 1
