// buffer.h
#include "Net.h"
#ifndef BUFFER_H
#define BUFFER_H

using BufType = char; // for easy rewrite with template

namespace Net
{
    class Buffer // todo: use template
    {
    private:
        BufType *Buf;
        int BufSize;
    public:
        int getSize();
        void resize(int);

        BufType* getBuf();
        void setBuf(BufType* buf);
        //BufType& at(int); todo
    public:
        Buffer(int, BufType*);
        Buffer(int);
        Buffer();
        ~Buffer();
    };
        
} // namespace Net

#endif
