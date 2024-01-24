#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>
#include "secrets.h"
#include "device.h"

/**
 * @author Antonios Karagiannis (antokarag@gmail.com)
 * @brief definitions for the Device
 * @date 2024-01-23
 *
 * @copyright Copyright (c) 2024
 *
 */

/**
 * @brief Wifi status as of last check.
 * Hence, it may not be up to date on every loop iteration.
 */
int Device::wifiStatus;

/**
 * @brief the wifi client
 *
 */
WiFiClient Device::client;

/**
 * @brief flag to keep track of the first loop
 */
bool Device::firstLoop = true;

/**
 * @brief flag to keep track of when we just reconnected
 */
bool Device::reconnected = false;

/**
 * @brief last time we performed a wifi check (ie. if still connected or not)
 */
unsigned long Device::lastWifiCheck = millis();

void Device::connectToWifi()
{
  // get our WiFi's mac address
  byte mac[WL_MAC_ADDR_LENGTH];
  WiFi.macAddress(mac);

  // connect to WiFi
  while (Device::wifiStatus != WL_CONNECTED)
  {
#ifdef SERIAL_DEBUG
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(WIFI_SSID);
#endif
    Device::wifiStatus = WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
    // wait to connect...
    delay(WAIT_FOR_WIFI);
  }

#ifdef SERIAL_DEBUG
  Serial.print("Connected to: ");
  Serial.print(WIFI_SSID);
  Serial.print(", with IP: ");
  Serial.print(WiFi.localIP());
  Serial.print(" and mac: ");
  Serial.print(mac[5], HEX);
  Serial.print(":");
  Serial.print(mac[4], HEX);
  Serial.print(":");
  Serial.print(mac[3], HEX);
  Serial.print(":");
  Serial.print(mac[2], HEX);
  Serial.print(":");
  Serial.print(mac[1], HEX);
  Serial.print(":");
  Serial.println(mac[0], HEX);
#endif
}

/**
 * @brief enables OTA (over the air updates)
 *
 */
void Device::setupOTA()
{
  ArduinoOTA.setHostname(DEVICE_ID);
  ArduinoOTA.setPassword(OTA_PASSWORD);
  ArduinoOTA.onStart([]()
                     {
                       String type;
                       if (ArduinoOTA.getCommand() == U_FLASH)
                       {
                         type = "sketch";
                       }
                       else
                       { // U_FS
                         type = "filesystem";
                       }

// NOTE: if updating FS this would be the place to unmount FS using FS.end()
#ifdef SERIAL_DEBUG
                       Serial.println("Start updating " + type);
#endif
                     });
  ArduinoOTA.onEnd([]()
                   {
#ifdef SERIAL_DEBUG
                     Serial.println("\nEnd");
#endif
                   });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total)
                        {
#ifdef SERIAL_DEBUG
                          Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
#endif
                        });
  ArduinoOTA.onError([](ota_error_t error)
                     {
#ifdef SERIAL_DEBUG
                       Serial.printf("Error[%u]: ", error);
                       if (error == OTA_AUTH_ERROR)
                       {
                         Serial.println("Auth Failed");
                       }
                       else if (error == OTA_BEGIN_ERROR)
                       {
                         Serial.println("Begin Failed");
                       }
                       else if (error == OTA_CONNECT_ERROR)
                       {
                         Serial.println("Connect Failed");
                       }
                       else if (error == OTA_RECEIVE_ERROR)
                       {
                         Serial.println("Receive Failed");
                       }
                       else if (error == OTA_END_ERROR)
                       {
                         Serial.println("End Failed");
                       }
#endif
                     });
  ArduinoOTA.begin();
}

/**
 * @brief let's us know if everything is connected and therefore,
 * "safe" to send data to the controller
 *
 * @return true when WiFi and everything else is connected
 * @return false when disconnected
 */
bool Device::isConnected()
{
  return Device::wifiStatus == WL_CONNECTED;
}

/**
 * @brief checks periodically if the WiFi connection is still connected and
 * attempts to reconnect if not connected.
 *
 */
void Device::wifiLoop()
{
  if (Device::reconnected)
  {
    // clear the reconnected flag
    Device::reconnected = false;
  }

  if (abs(long(millis() - Device::lastWifiCheck)) > WIFI_CHECK_FREQUENCY)
  {
    Device::lastWifiCheck = millis();
    Device::wifiStatus = WiFi.status();
    if (!Device::isConnected())
    {
      WiFi.disconnect();
      Device::connectToWifi();
      // we just reconnected to the WiFi
      // set this flag, it will be reset on the next iteration (see above)
      // this flag lets the whole application know, when a reconnection just took place
      Device::reconnected = true;
    }
  }
}

/**
 * @brief should be called once, from the main setup() function
 *
 */
void Device::setup()
{
#ifdef SERIAL_DEBUG
  Serial.begin(9600);
  delay(500); // Give the serial terminal a chance to connect, if present
  Serial.print("Device::Setup()");
#endif

  Device::connectToWifi();

  // enable OTA
  Device::setupOTA();
}

/**
 * @brief should be called on every iteration of the main loop() function
 *
 */
void Device::loop()
{
  // process any incoming OTA requests
  ArduinoOTA.handle();

  /**
   * @brief only on the first loop,
   *        swap the status to force an update of the status sensor,
   *        in order to have a record of the time the device rebooted...
   *
   */
  if (Device::firstLoop)
  {
    Device::firstLoop = false;
  }

  // check if wifi is still connected, etc.
  Device::wifiLoop();
}