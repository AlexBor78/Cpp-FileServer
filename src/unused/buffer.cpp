#include "buffer.h"

namespace Net
{
    Buffer::~Buffer()
    {

    }

    Buffer::Buffer(int size, BufType* buf)
    :
    BufSize(size),
    Buf(buf)
    {}
    Buffer::Buffer(int size)
    :
    BufSize(size),
    Buf(new BufType[BufSize])
    {}
    Buffer::Buffer()
    :
    BufSize(-1),
    Buf(new BufType())
    {}
    
    //BufType& at(int i)
    //{
    //    return buf[i];
    //}

    BufType* Buffer::getBuf()
    {
        return Buf;
    }
    void Buffer::setBuf(BufType* buf)
    {
        Buf = buf;
    }

    int Buffer::getSize()
    {
        return BufSize;
    }
    void Buffer::resize(int size)
    {
        BufSize = size;
        Buf = new BufType[BufSize];
    }

} // namespace Net
