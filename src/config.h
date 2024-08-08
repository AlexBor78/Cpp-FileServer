/*
 * This file is config to server and client.
 * You can change some preferens,
 * But NEVER CHANGE NAMES OF PREFERENS.
 * Default settings is the best.
 * 
 * in () will write who use this preference
 */

// this port and IP adress of server, and to that client connecting (server and client)
#define PORT 7633
#define IP "127.0.0.2"



// server preferens (server)

// is max number of clients in queue
#define SERVER_MAX_CLIENTS_QUEUE 5 // recommend: 5 - 15

// pasword to admin-client 
#define SERVER_ADMIN_PASWORD "01234567"



// log preferens (server and client)

// If one of all conditions will be fulfilled, will create new log-file

// number of lines befor file will close and create new log-file
#define LOG_MAX_SIZE 10000 

// max log-file size, if file size > MAX_LOG_FILE_SIZE file will close and create new fill
#define LOG_MAX_FILE_SIZE 1 * MB



// send/recv files preferens (server and client)

// не менять эти значения
// Dont't change this values
#define KB pow(2, 10) // 1KB
#define MB pow(2, 20) // 1MB
#define GB pow(2, 30) // 1GB
// #define TB pow(2, 40) // 1TB
// #define PB pow(2, 50) // 1PB

// Max file size to send to server and recv on client
#define FILE_MAX_SIZE 1 * MB // = 1 MB

// Total max files size 
#define FILES_MAX_SUM_SIZE 1 * GB // = 1GB
