/*
 * ExternalMessageManager header file which contains the functions used in system for communication between nodes
 *
 * Developed by: Adrián Pacera, Iskren Zhechev (T3-CB02)
 */
#pragma once

#include <queue>
#include "ESPNOW.hpp"
#include "MessageESPNOW.hpp"
#include "IExternalMessageSend.hpp"

namespace NodeCommunication
{
    class ExternalMessageManager : public IExternalMessageSend
    {
    private:
        std::queue<MessageESPNOW> incomingMessageQueue;
        std::queue<MessageESPNOW> outgoingMessageQueue;
    public:

        ExternalMessageManager();

        void enqueueMessage(const MessageESPNOW &message);
        bool dequeueMessage(MessageESPNOW &message);
        int sendMessage(const MessageESPNOW &message) override;

        //this function will send recieved message to NodeManager via interface
        //void recieveLocalMessage(MessageESPNOW &message) override;
    };
}