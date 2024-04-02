#ifndef DATA_STORE
#define DATA_STORE
#include <Arduino.h>
#include <EEPROM.h>

/**
 * @brief memory structure
 *
 * mem. address offset : description/purpose
 *
 * overall:
 *  0: has stored flag
 *  1: data store version
 *  2-9: reserved
 *  10: start of data items
 *
 * data item:
 *  0: type of variable
 *      0-10: reserved
 *      11: byte
 *      12: bool
 *      13: char
 *      14: int
 *      15: float
 *      16: String
 *  1: bytes of variable N
 *  2-5: reserved
 *  6...N: byte data of variable
 *  N+1: next-flag
 *      0-10: reserved
 *      11:   next data item
 *      12:   end of data items
 *
 */

/**
 * @brief max. number of bytes we can store in EEPROM
 *        about 34 bytes per preset
 *        x10 presets, that is a total of 340 bytes
 */
// TODO: check if we can use sizeof here
#define EEPROM_SIZE_BYTES 512

/**
 * @brief mem. address of the flag that let's us know
 * if we have previously stored any data
 *
 */
#define EEPROM_HAS_STORED_DATA_FLAG_ADDRESS 0

/**
 * @brief the value to look for in mem. to know that we
 * have previously stored data
 *
 * this can only be 1 byte (0-255).
 * it appears that the "Default" value is 255,
 * when we haven't previously written anything there...
 */
#define EEPROM_HAS_STORED_DATA_FLAG_VALUE 125

/**
 * @brief version of data previously stored
 * e.g. in case we make a breaking change in the data structure,
 * we need to overwrite with defaults...
 *
 * this can only be 1 byte (0-255)
 */
#define EEPROM_HAS_STORED_DATA_VER_VALUE 1

class Data_Store
{
    /**
     * @brief if true, there's setData that needs to be saved
     *
     */
    static bool pendingSave;

    /**
     * @brief current memory address (read/write)
     *
     */
    static unsigned int mem_address;

public:
    static void setup();
    static bool hasStoredData();
    template <typename T>
    static void numberToBytes(T value, byte *byteArray);
    static bool save();
    static void setIntData(int value);
    static void setFloatData(float value);
    static void setData(String value);
    static int bytesToInt(byte *byteArray);
    static float bytesToFloat(byte *byteArray);
};

#endif // DATA_STORE
