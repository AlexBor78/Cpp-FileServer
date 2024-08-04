#include "Net.h"

#ifndef ERROR_H
#define ERROR_H 1

namespace Net
{
    class Error
    {
    private:
        const char* ErrMsg;
        int ErrCode;
    public:
        const char* getErrMessage();
        int getErrCode();
    public:
        Error(int, const char*);
        ~Error();
    };
} // namespace Net

#endif
