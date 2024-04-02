#include <Arduino.h>
#include "ExternalMessageManager.hpp"

using namespace NodeCommunication;

ExternalMessageManager manager;


void setup() {
    Serial.begin(9600);

    manager = ExternalMessageManager();
}

void loop() {
    //these values will be taken from shared lib
    uint8_t MAC_N[] = {0x78, 0xE3, 0x6D, 0x09, 0xE1, 0xD0};
    uint8_t MAC_S[] = {0x94, 0xB9, 0x7E, 0xE6, 0x2E, 0xA4};
    char arguements[ARUEMENTS_LENGHT] = "Hi from north";

    MessageESPNOW message(MessageESPNOW::Message_type::Standard, arguements, MAC_N, MAC_S);

    manager.sendMessage(message);

    delay(1000);
}


