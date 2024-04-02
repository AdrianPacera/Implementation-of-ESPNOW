#include "MessageESPNOW.hpp"

namespace NodeCommunication 
{
    MessageESPNOW::MessageESPNOW(Message_type type, char arguements[], uint8_t sourceMAC[], uint8_t destinationMAC[]) {
        data.type = type;
        std::copy(arguements, arguements + ARUEMENTS_LENGHT, data.arguements);
        std::copy(sourceMAC, sourceMAC + MAC_SIZE, data.sourceMAC);
        std::copy(destinationMAC, destinationMAC + MAC_SIZE, data.destinationMAC);
    }

    MessageESPNOW MessageESPNOW::createDefault()
    {
        //these values will be taken from shared lib
        uint8_t MAC_N[] = {0x78, 0xE3, 0x6D, 0x09, 0xE1, 0xD0};
        uint8_t MAC_S[] = {0x94, 0xB9, 0x7E, 0xE6, 0x2E, 0xA4};
        char arguements[ARUEMENTS_LENGHT] = "NONE";
        
        MessageESPNOW message(MessageESPNOW::Message_type::Standard, arguements, MAC_N, MAC_S);
        return message;
    }
};