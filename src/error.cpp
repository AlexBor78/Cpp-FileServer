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

    int Error::getErrCode()
    {
        return ErrCode;
    }
    const char* Error::getErrMessage()
    {
        return ErrMsg;
    }
} // namespace Net
