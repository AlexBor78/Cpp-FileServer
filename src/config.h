/*
 * This file is config to server and client.
 * You can change some preferens,
 * But NEVER CHANGE NAMES OF PREFERENS.
 * Default settings is the best.
 * 
 * in () will write who use this preference
 */

// this port and IP adress of server, and to that client connecting (server and client)
#define PORT 7635
#define IP "192.168.188.236"



// server preferens (server)

// is max number of clients in queue
#define SERVER_MAX_CLIENTS_QUEUE 5 // recommend: 5 - 15

// pasword to admin-client 
#define SERVER_ADMIN_PASWORD "01234567"

#define SERVER_LOG_FILE "data/ServerLog"
#define SERVER_DATA_FILE "data/ServerData"



// log preferens (server and client)

// If one of all conditions will be fulfilled, will create new log-file

// number of lines befor file will close and create new log-file
#define LOG_MAX_SIZE 10000 

// max log-file size, if file size > LOG_MAX_FILE_SIZE file will close and create new fill
#define LOG_MAX_FILE_SIZE MB



// send/recv files preferens (server and client)

// не менять эти значения
// Dont't change this values
#define KB 1024 // pow(2, 10) // 1KB
#define MB 1048576 // pow(2, 20) // 1MB
#define GB 1'073'741'824 // pow(2, 30) // 1GB
// #define TB pow(2, 40) // 1TB
// #define PB pow(2, 50) // 1PB

// Max file size to send to server and recv on client
#define FILE_MAX_SIZE MB // = 1 MB

// Total max files size 
#define FILES_MAX_SUM_SIZE GB // = 1GB

// size of send blocks of file
#define FILE_BLOCK_SIZE KB 
