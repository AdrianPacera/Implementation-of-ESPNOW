/*
 * ESPNOW header file which contains the function bodies for using ESPNOW protocol in mesh
 *
 * Developed by: Adrián Pacera, Iskren Zhechev (T3-CB02)
*/
#pragma once

#include "MessageESPNOW.hpp"
#include "WiFi.h"
#include <esp_now.h>
#include <WiFi.h>

#define MAC_SIZE 6

namespace NodeCommunication {

    void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status);

    void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len);

    void ESPNOWInitialize();

    int sendProtocolMessage(NodeCommunication::MessageESPNOW message);

    int ESPNOWAddPeer(esp_now_peer_info peer, uint8_t MAC[]);
} 


