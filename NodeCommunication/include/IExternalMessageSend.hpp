#pragma once

namespace NodeCommunication
{
    class IExternalMessageSend
    {
    public:
        //returns 0 on success, -1 if message was not sent correctly (this is for error handling, if not neccessary this function can be used in same way as void function)
        virtual int sendMessage(const MessageESPNOW &message) = 0;
    };

}
