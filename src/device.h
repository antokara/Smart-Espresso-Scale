#ifndef DEVICE
#define DEVICE

#define DEVICE_ID "smart-espresso-scale"
#define DEVICE_NAME "Smart Espresso Scale"
#define FIRMWARE_VERSION "1.0.0"

// uncomment to enable serial.print debug messages
#define SERIAL_DEBUG

class Device
{
public:
    // properties
    static bool firstLoop;
    static bool reconnected;

    // methods
    static void setup();
    static void loop();
};

#endif // DEVICE