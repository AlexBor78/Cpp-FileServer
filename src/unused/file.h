// file.h
#include "Net.h"
#ifndef FILE_H
#define FILE_H 1
//#define _FILE_BUF_SIZE 1024

namespace Net
{
    class File
    {
    private:
        std::string FilePath, FileName;
        std::fstream file;
        uint64_t FileSize;
        char* FileBuf;
    public:
        void open(std::string, std::string);
        void open(std::string);
        void open();
        void close();

        Net::Buffer getBuf();
        bool isAll();
        void setPath(std::string);
        std::string getPath(); 
        std::string getName();       
    public:
        File(std::string, std::string);
        File(std::string);
        File();
        ~File();
    };
    
} // namespace Net
#endif
