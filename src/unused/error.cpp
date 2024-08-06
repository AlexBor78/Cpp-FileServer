#include "error.h"

namespace Net
{
    Error::~Error()
    {

    }

    Error::Error(int errcode, const char* msg)
    :
    ErrCode(errcode),
    ErrMsg(msg)
    {}
    Error::Error(const char* msg)
    :
    ErrCode(-1),
    ErrMsg(msg)
    {}

    int Error::getErrCode()
    {
        return ErrCode;
    }
    const char* Error::what()
    {
        return ErrMsg;
    }
} // namespace Net
