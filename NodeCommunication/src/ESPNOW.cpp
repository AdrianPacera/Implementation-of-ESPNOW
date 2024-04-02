/*
 * ESPNOW source file which implements the functions in ESPNOW.hpp
 *
 * Developed by: Adrián Pacera, Iskren Zhechev (T3-CB02)
*/

#include "ESPNOW.hpp"
#include "ExternalMessageManager.hpp"
#include "MessageESPNOW.hpp"

using namespace std;

namespace NodeCommunication {
    //these values will be taken from shared lib
    uint8_t MAC_N[] = {0x78, 0xE3, 0x6D, 0x09, 0xE1, 0xD0};
    uint8_t MAC_S[] = {0x94, 0xB9, 0x7E, 0xE6, 0x2E, 0xA4};
    uint8_t MAC_W[] = {0xB0, 0xB2, 0x1C, 0x0A, 0xF3, 0x88};
    uint8_t MAC_E[] = {0xC8, 0xF0, 0x9E, 0x75, 0x28, 0x08};

    //these values will be taken from shared lib
    esp_now_peer_info_t peerInfo_N;
    esp_now_peer_info_t peerInfo_S;
    esp_now_peer_info_t peerInfo_W;
    esp_now_peer_info_t peerInfo_E;
    
    //this can be removed if no error handling is happening regarding send status of send message (depends on logic in namespace NodeManager)
    void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
        
        if(std::equal(mac_addr, mac_addr+MAC_SIZE, MAC_N)) {
            Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery North Success" : "Delivery North Fail");
        }

        if(std::equal(mac_addr, mac_addr+MAC_SIZE, MAC_S)) {
            Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery South Success" : "Delivery South Fail");
        }

        if(std::equal(mac_addr, mac_addr+MAC_SIZE, MAC_W)) {
            Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery West Success" : "Delivery West Fail");
        }

        if(std::equal(mac_addr, mac_addr+MAC_SIZE, MAC_E)) {
            Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery East Success" : "Delivery East Fail");
        }
    }

    void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
        ExternalMessageManager manager = ExternalMessageManager();
        MessageESPNOW recievedMessage = MessageESPNOW::createDefault();

        //this memory copy has to stay due to lib arguements which are casted to const uint8_t and cant be typecasted to something else
        //also, memcpy is C++ native so the only downside is a debug factor...
        memcpy(&recievedMessage.data, incomingData, sizeof(recievedMessage.data));

        //this will send recieved message to NodeManagment via interface 
        //manager.recieveLocalMessage(recievedMessage);

        //these if statements are not neccessary if we dont care from which MAC the message was sent as of im not sure about logic in NodeManager
        if(std::equal(mac, mac+MAC_SIZE, MAC_N)) {
            Serial.println(recievedMessage.data.arguements);
        }

        if(std::equal(mac, mac+MAC_SIZE, MAC_S)) {
            Serial.println(recievedMessage.data.arguements);
        }
        if(std::equal(mac, mac+MAC_SIZE, MAC_W)) {
            Serial.println(recievedMessage.data.arguements);
        }

        if(std::equal(mac, mac+MAC_SIZE, MAC_E)) {
            Serial.println(recievedMessage.data.arguements);
        }

        
        
    }

    int ESPNOWAddPeer(esp_now_peer_info peer, uint8_t mac_addr[]){
        //this memory copy can be potentially changed to a more cpp function, however std::copy didnt function properly, reason is unknown
        memcpy(peer.peer_addr, mac_addr, 6);
        peer.channel = 0;  
        peer.encrypt = false;

        if(esp_now_add_peer(&peer) != ESP_OK ){
            return -1;
        }   

        return 0; 
    }

    int wifiSetup(){
        WiFi.mode(WIFI_STA);

        if (esp_now_init() != ESP_OK) {
            return -1;
        }

        return 0;
    }

    void ESPNOWInitialize() {
        //remove monitor after testing
        Serial.begin(9600);

        wifiSetup();

        ESPNOWAddPeer(peerInfo_N, MAC_N);
        ESPNOWAddPeer(peerInfo_S, MAC_S);
        ESPNOWAddPeer(peerInfo_W, MAC_W);
        ESPNOWAddPeer(peerInfo_E, MAC_E);

        esp_now_register_send_cb(OnDataSent);
        esp_now_register_recv_cb(OnDataRecv);
    }

    int sendProtocolMessage(MessageESPNOW message) {

        esp_err_t sendResult = esp_now_send(message.data.destinationMAC, (uint8_t *) &message.data, sizeof(message.data));

        if(sendResult != ESP_OK){
            return -1;
        }

        return 0;
    }
} 
