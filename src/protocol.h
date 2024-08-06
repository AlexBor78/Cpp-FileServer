// protocol.h
#include "Net.h"

#ifndef PROTOCOL_H
#define PROTOCOL_H 1

namespace Net
{
    class Protocol
    {
    public:
        static const unsigned int HeadSize = 8;
        static const unsigned int MiddleSize = 1;
    public:
        class Head
        {
        public: enum ActionType : uint8_t
            {
                SendMessage = 10,
                #define SendMessage Protocol::Head::ActionType::SendMessage

                SendData = 20,
                #define SendData Protocol::Head::ActionType::SendData

                SendFile = 30,
                #define SendFile Protocol::Head::ActionType::SendFile

                ChekConnect = 0,
                #define ChekConnect Protocol::Head::ActionType::ChekConnect

                EndSesion = 255
                #define EndSesion Protocol::Head::ActionType::EndSesion
            };
        public:
            uint8_t MajorVersion;  // for future
            uint8_t MinorVersion1; // for future
            uint8_t MinorVersion2; // for future
            ActionType Action;
            uint32_t AdditionalData;
        };
        
        class Middle
        {
        public:
            enum ActionStatus : bool
            {
                SuccesAction = 1,
                #define SuccesAction Net::Protocol::Middle::ActionStatus::SuccesAction

                FaildAction = 0
                #define FaildAction Net::Protocol::Middle::ActionStatus::FaildAction
            };
        public:
            ActionStatus Status;
        };
    };
} // namespace Net
#endif
