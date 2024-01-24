#ifndef DEVICE
#define DEVICE

#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#define DEVICE_ID "smart-espresso-scale"
#define DEVICE_NAME "Smart Espresso Scale"
#define FIRMWARE_VERSION "1.0.0"

// uncomment to enable serial.print debug messages
#define SERIAL_DEBUG

/**
 * @brief time in milliseconds to wait for the WiFi to connect
 *
 */
#define WAIT_FOR_WIFI 5000

/**
 * @brief frequence in milliseconds,
 * to check for the Wifi connection status
 */
#define WIFI_CHECK_FREQUENCY 10000

class Device
{
public:
    // properties
    static int wifiStatus;
    static WiFiClient client;
    static bool firstLoop;
    static bool reconnected;
    static unsigned long lastWifiCheck;

    // methods
    static void connectToWifi();
    static bool isConnected();
    static void wifiLoop();
    static void setupOTA();
    static void setup();
    static void loop();
};

#endif // DEVICE