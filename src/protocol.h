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
        static const unsigned int MiddleSize = 32;
        static const unsigned int EndSize = 1;
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
        public:
            Head(ActionType, uint32_t);
            Head(ActionType);
            Head();
        };

        class Middle
        {
        private:
            uint64_t Data1;
            uint64_t Data2;
            uint64_t Data3;
            uint64_t Data4;
        public:
            Middle();
        };

        class End
        {
        public: enum ActionStatus : bool
            {
                SuccesAction = 1,
                #define SuccesAction Net::Protocol::End::ActionStatus::SuccesAction

                FaildAction = 0
                #define FaildAction Net::Protocol::End::ActionStatus::FaildAction
            };
        public:
            ActionStatus Status;
        public:
            End(ActionStatus);
            End();
        };
    };
} // namespace Net
#endif
