/*
 * ExternalMessageManager source file which contains the implementation of functions from header file ExternalMessageManager.hpp
 *
 * Developed by: Adrián Pacera, Iskren Zhechev (T3-CB02)
 */

#include "ExternalMessageManager.hpp"

namespace NodeCommunication
{
    ExternalMessageManager::ExternalMessageManager(){
        ESPNOWInitialize();
    }

    void ExternalMessageManager::enqueueMessage(const MessageESPNOW &message)
    {
        outgoingMessageQueue.push(message);
    }

    bool ExternalMessageManager::dequeueMessage(MessageESPNOW &message)
    {
        if (!outgoingMessageQueue.empty())
        {
            message = outgoingMessageQueue.front();
            outgoingMessageQueue.pop();
            return true;
        }
        return false;
    }

    int ExternalMessageManager::sendMessage(const MessageESPNOW &message)
    {
        enqueueMessage(message);


        MessageESPNOW frontMessage = outgoingMessageQueue.front();

        
        
        int sendResult = sendProtocolMessage(frontMessage);

        if(sendResult != 0){
            return -1;
        }

        outgoingMessageQueue.pop();


        return 0;
    }
}