#ifndef IR
#define IR
#include <Arduino.h>

/**
 * @brief Infrared Transmitter DAT pin
 * D0-D28 which equates to GP0-GP28.
 */
#define IR_SEND_PIN D5

class Ir
{
public:
    // methods
    static void setup();
    static void loop();
    static void send();

    /*
     * Set up the data to be sent.
     * The compiler is intelligent and removes the code for 16 bit address handling if we call it with an uint8_t address :-).
     * Using an uint16_t address or data requires additional 28 bytes program memory for NEC and 56 bytes program memory for FAST.
     */
    static uint8_t sendAddress;
    static uint8_t sendCommand;
    static uint8_t sendRepeats;
};

#endif // IR
