// data.cpp
#include "data.h"

namespace Net
{
    Data::~Data()
    {}

    Data::Data(void* ptr, unsigned int size)
    :
    DataPtr(ptr),
    DataSize(size)
    {}
    Data::Data()
    :
    DataPtr(nullptr),
    DataSize(-1)
    {}

    unsigned int Data::getSize()
    {
        return DataSize;
    }

    void* Data::getPtr()
    {
        return DataPtr;
    }

    void Data::set(void* ptr, unsigned int size)
    {
        DataPtr = ptr;
        DataSize = size;
    }
    
} // namespace Net
