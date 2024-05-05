#ifndef DATA_STORE
#define DATA_STORE
#include <Arduino.h>
#include <EEPROM.h>
#include <services/device.h>
#include <services/presets/presets.h>
#include <services/data_store_types.h>
#include <services/data_store_next_flag.h>

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
 *      16: string
 *  1-4: bytes of variable N (sizeOf(int))
 *  5...N: byte data of variable
 *  N+1: next-flag
 *      0-10: reserved
 *      11:   next data item
 *      12:   end of data items
 *
 */

/**
 * @brief max. number of bytes we can store in EEPROM
 *        size of preset + max string size of preset name + control bytes
 *        x10 presets, that is a total of about 400 bytes + 20 for data_store control bytes
 */
#define DATA_STORE_SIZE_BYTES (sizeof(Preset) + 5 + 25) * PRESETS_COUNT + 30

/**
 * @brief mem. address of the flag that let's us know
 * if we have previously stored any data
 *
 */
#define DATA_STORE_HAS_STORED_DATA_FLAG_ADDRESS 0

/**
 * @brief the value to look for in mem. to know that we
 * have previously stored data
 *
 * this can only be 1 byte (0-255).
 * it appears that the "Default" value is 255,
 * when we haven't previously written anything there...
 */
#define DATA_STORE_HAS_STORED_DATA_FLAG_VALUE 125

/**
 * @brief mem. address of the version
 *
 */
#define DATA_STORE_VERSION_ADDRESS DATA_STORE_HAS_STORED_DATA_FLAG_ADDRESS + 1

/**
 * @brief version of data previously stored
 * e.g. in case we make a breaking change in the data structure,
 * we need to overwrite with defaults...
 *
 * this can only be 1 byte (0-255)
 */
#define DATA_STORE_VERSION_VALUE 1

/**
 * @brief mem. address of the first data item
 *
 */
#define DATA_STORE_DATA_ITEMS_ADDRESS DATA_STORE_VERSION_ADDRESS + 9

/**
 * @brief max. number of characters a string can have
 * (excl. null terminator)
 */
#define DATA_STORE_MAX_STRING_LENGTH 20

class Data_Store
{
    /**
     * @brief if true, there's written that needs to be saved
     *
     */
    static bool pendingSave;

    /**
     * @brief if true, we're currently reading data
     *
     */
    static bool pendingLoad;

    /**
     * @brief current memory address (read/write)
     *
     */
    static unsigned int mem_address;

public:
    static void setup();

    static void writeData(data_store_types type, byte *byteArray, int data_length);
    static void writeByteArray(byte *byteArray, int sizeOfByteArray);
    static void writeByteData(byte value);
    static void writeBoolData(bool value);
    static void writeCharData(char value);
    static void writeIntData(int value);
    static void writeFloatData(float value);
    static void writeStringData(String value);
    static bool save();

    template <typename T>
    static void convertToBytes(T value, byte *byteArray);
    static void stringToBytes(String str, byte *byteArray);

    static bool hasStoredData();
    static int bytesToInt(byte *byteArray);
    static float bytesToFloat(byte *byteArray);
    static void readBytes(int data_length, byte *byteArray);
    static int readData(data_store_types type, byte *byteArray);
    static byte readByteData();
    static bool readBoolData();
    static char readCharData();
    static int readIntData();
    static float readFloatData();
    static String readStringData();
};

#endif // DATA_STORE

// Test Code:
// Data_Store::writeByteData(15);
// Data_Store::writeBoolData(true);
// Data_Store::writeCharData('X');
// Data_Store::writeIntData(1024);
// Data_Store::writeFloatData(123.456);
// Data_Store::writeStringData("testing!");
// Data_Store::save();

// byte byte_val = Data_Store::readByteData();
// Serial.println("byte_val: ");
// Serial.println(byte_val);

// bool bool_val = Data_Store::readBoolData();
// Serial.println("bool_val: ");
// Serial.println(bool_val);

// char char_val = Data_Store::readCharData();
// Serial.println("char_val: ");
// Serial.println(char_val);

// int int_val = Data_Store::readIntData();
// Serial.println("int_val: ");
// Serial.println(int_val);

// float float_val = Data_Store::readFloatData();
// Serial.println("float_val: ");
// Serial.println(float_val);

// String str_val = Data_Store::readStringData();
// Serial.println("str_val: ");
// Serial.println(str_val);
