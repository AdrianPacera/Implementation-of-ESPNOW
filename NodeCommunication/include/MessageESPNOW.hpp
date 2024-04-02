#pragma once

#include <array>
#define ARUEMENTS_LENGHT 32
#define MAC_SIZE 6


namespace NodeCommunication
{   
    class MessageESPNOW
    {
    public:
        enum class Message_type
        {
            Standard,
            Shush,
            Emergency,
            Acknowledgment
        };

        typedef struct Message_struct
        {
            Message_type type;
            char arguements[ARUEMENTS_LENGHT];
            uint8_t sourceMAC[MAC_SIZE];
            uint8_t destinationMAC[MAC_SIZE];
        } Message_struct;

        MessageESPNOW(Message_type type, char arguements[], uint8_t sourceMAC[], uint8_t destinationMAC[]);

        static MessageESPNOW createDefault();

        Message_struct data;
    };
};
