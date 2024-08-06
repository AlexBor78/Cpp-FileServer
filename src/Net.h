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

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

namespace Net
{
    class Server; // done
    class Client; // done
    
    class Buffer; // done
    class File; // done
    class Data; // done
    //class Error; // trash // don't use
    //class Logger; // done redefinition or incomplet, what the fuck?
} // namespace Net

#include "error.h"
#include "buffer.h"
//#include "logger.h"
#include "data.h"
#include "file.h"
#include "server.h"
#include "client.h"

#define NET_H 1
