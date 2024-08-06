// data.h
#include "Net.h"
#ifndef DATA_H
#define DATA_H 1

namespace Net
{
    class Data
    {
    private:
        unsigned int DataSize;
        void* DataPtr;
    public:
        void set(void*, unsigned int);
        unsigned int getSize();
        void* getPtr();
    public:
        Data(void*, unsigned int);
        Data();
        ~Data();
    };
    
} // namespace Net
#endif
