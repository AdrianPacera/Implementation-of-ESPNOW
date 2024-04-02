#include <Arduino.h>
#include <unity.h>
#include "ESPNOW.hpp"
#include "ESPNOW.cpp"
#include "ExternalMessageManager.hpp"
#include "ExternalMessageManager.cpp"
#include "MessageESPNOW.hpp"
#include "MessageESPNOW.cpp"
#include <esp_now.h>

using namespace NodeCommunication;

// Test if the wifi setup function returns 0 on success
void test_wifi_setup(void)
{
    TEST_ASSERT_EQUAL(0, wifiSetup());
}

// Test if the ESPNOW add peer function returns 0 on success
void test_espnow_add_peer(void)
{
    TEST_ASSERT_EQUAL(0, ESPNOWAddPeer(peerInfo_N, MAC_N));
    TEST_ASSERT_EQUAL(0, ESPNOWAddPeer(peerInfo_S, MAC_S));
    TEST_ASSERT_EQUAL(0, ESPNOWAddPeer(peerInfo_W, MAC_W));
    TEST_ASSERT_EQUAL(0, ESPNOWAddPeer(peerInfo_E, MAC_E));
}

void test_send_protocol_message(void)
{
    NodeCommunication::MessageESPNOW message = NodeCommunication::MessageESPNOW::createDefault();
    message.data.arguements[0] = 42;
    memcpy(message.data.destinationMAC, MAC_N, 6);
    TEST_ASSERT_EQUAL(0, sendProtocolMessage(message));
}

void test_dequeue_message(void)
{
    ExternalMessageManager manager;
    NodeCommunication::MessageESPNOW message = NodeCommunication::MessageESPNOW::createDefault();

    // Add a message to the queue
    manager.enqueueMessage(message);

    // Dequeue the message and check if it matches the one added
    NodeCommunication::MessageESPNOW dequeuedMessage = NodeCommunication::MessageESPNOW::createDefault();
    bool dequeued = manager.dequeueMessage(dequeuedMessage);

    TEST_ASSERT_TRUE(dequeued);
    TEST_ASSERT_EQUAL_MEMORY(&message, &dequeuedMessage, sizeof(MessageESPNOW));
}

void test_send_message(void)
{
    ExternalMessageManager manager;
    NodeCommunication::MessageESPNOW message = NodeCommunication::MessageESPNOW::createDefault();

    int result = manager.sendMessage(message);

    TEST_ASSERT_EQUAL(0, result);
}

void test_create_default_message()
{
    // Create a default message
    NodeCommunication::MessageESPNOW message = NodeCommunication::MessageESPNOW::createDefault();

    // Check if the message fields match the expected default values
    TEST_ASSERT_EQUAL(NodeCommunication::MessageESPNOW::Message_type::Standard, message.data.type);
    TEST_ASSERT_EQUAL_STRING("NONE", message.data.arguements);
    uint8_t expectedSourceMAC[] = {0x78, 0xE3, 0x6D, 0x09, 0xE1, 0xD0};
    uint8_t expectedDestinationMAC[] = {0x94, 0xB9, 0x7E, 0xE6, 0x2E, 0xA4};
    // Update the macro references in your test cases
    TEST_ASSERT_EQUAL_MEMORY(expectedSourceMAC, message.data.sourceMAC, MAC_SIZE);
    TEST_ASSERT_EQUAL_MEMORY(expectedDestinationMAC, message.data.destinationMAC, MAC_SIZE);
}

void setup()
{
    delay(2000);
    UNITY_BEGIN();

    // Add your test functions here
    RUN_TEST(test_wifi_setup);
    RUN_TEST(test_espnow_add_peer);
    RUN_TEST(test_send_protocol_message);
    RUN_TEST(test_dequeue_message);
    RUN_TEST(test_send_message);
    RUN_TEST(test_create_default_message);

    delay(1000);
    UNITY_END();
}

void loop()
{
    // No need for a loop in unit tests
}
