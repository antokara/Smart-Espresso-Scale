#include "services/data_store.h"

bool Data_Store::pendingSave = false;
unsigned int Data_Store::mem_address = DATA_STORE_DATA_ITEMS_ADDRESS;

/**
 * @brief must be called before all other services,
 *        so that they can use it
 *
 */
void Data_Store::setup()
{
    EEPROM.begin(DATA_STORE_SIZE_BYTES);
}

/**
 * @brief checks if there's stored data (in EEPROM)
 *        for the current version.
 *
 * @return true
 * @return false
 */
bool Data_Store::hasStoredData()
{
    // check and see if we have previously stored any data
    byte hasStoredData = EEPROM.read(DATA_STORE_HAS_STORED_DATA_FLAG_ADDRESS);
    byte hasStoredDataVersion = EEPROM.read(DATA_STORE_VERSION_ADDRESS);
    return hasStoredData == DATA_STORE_HAS_STORED_DATA_FLAG_VALUE && hasStoredDataVersion == DATA_STORE_VERSION_VALUE;
}

/**
 * @brief converts a value to a byte array
 *
 * @param value can be int/float/double/char/boolean/etc.
 * @param byteArray
 */
template <typename T>
void Data_Store::convertToBytes(T value, byte *byteArray)
{
    memcpy(byteArray, &value, sizeof(value));
}

/**
 * @brief converts a string to a byte array
 *
 * @param str
 * @param byteArray
 */
void Data_Store::stringToBytes(String str, byte *byteArray)
{
    str.getBytes(byteArray, str.length() + 1); // +1 to include null terminator
}

/**
 * @brief commits to memory all the written data
 *
 * @return true
 * @return false
 */
bool Data_Store::save()
{
    Data_Store::pendingSave = false;
    EEPROM.write(Data_Store::mem_address, data_store_next_flag_end);
    if (!EEPROM.commit())
    {
#ifdef SERIAL_DEBUG
        Serial.println("ERROR! EEPROM commit failed");
#endif
    }
    return false;
}

/**
 * @brief writes the byte array to memory, byte-by-byte
 *
 * @param byteArray
 */
void Data_Store::writeByteArray(byte *byteArray)
{
    int sizeOfByteArray = sizeof(byteArray) / sizeof(byteArray[0]);
    for (int i = 0; i < sizeof(sizeOfByteArray); i++)
    {
        EEPROM.write(Data_Store::mem_address++, byteArray[i]);
    }
}

void Data_Store::writeData(data_store_types type, byte *byteArray)
{
    if (Data_Store::pendingSave)
    {
        EEPROM.write(Data_Store::mem_address++, data_store_next_flag_more);
    }
    else
    {
        EEPROM.write(DATA_STORE_HAS_STORED_DATA_FLAG_ADDRESS, DATA_STORE_HAS_STORED_DATA_FLAG_VALUE);
        EEPROM.write(DATA_STORE_VERSION_ADDRESS, DATA_STORE_VERSION_VALUE);
        Data_Store::mem_address = DATA_STORE_DATA_ITEMS_ADDRESS;
        Data_Store::pendingSave = true;
    }

    // type of variable we are about to store
    EEPROM.write(Data_Store::mem_address++, type);

    // number of bytes
    int sizeOfByteArray = sizeof(byteArray) / sizeof(byteArray[0]);
    byte sizeOfByteArrayBytes[sizeof(sizeOfByteArray)];
    Data_Store::convertToBytes(sizeOfByteArray, sizeOfByteArrayBytes);
    Data_Store::writeByteArray(sizeOfByteArrayBytes);

    // the actual data
    Data_Store::writeByteArray(sizeOfByteArrayBytes);
}

void Data_Store::writeByteData(byte value)
{
    byte bytes[sizeof(value)];
    Data_Store::convertToBytes(value, bytes);
    Data_Store::writeData(data_store_type_byte, bytes);
}

void Data_Store::writeBoolData(bool value)
{
    byte bytes[sizeof(value)];
    Data_Store::convertToBytes(value, bytes);
    Data_Store::writeData(data_store_type_bool, bytes);
}

void Data_Store::writeCharData(char value)
{
    byte bytes[sizeof(value)];
    Data_Store::convertToBytes(value, bytes);
    Data_Store::writeData(data_store_type_char, bytes);
}

void Data_Store::writeIntData(int value)
{
    byte bytes[sizeof(value)];
    Data_Store::convertToBytes(value, bytes);
    Data_Store::writeData(data_store_type_int, bytes);
}

void Data_Store::writeFloatData(float value)
{
    byte bytes[sizeof(value)];
    Data_Store::convertToBytes(value, bytes);
    Data_Store::writeData(data_store_type_float, bytes);
}

void Data_Store::writeStringData(String value)
{
    byte bytes[value.length()];
    Data_Store::stringToBytes(value, bytes);
    Data_Store::writeData(data_store_type_string, bytes);
}

int Data_Store::bytesToInt(byte *byteArray)
{
    int intValue;
    memcpy(&intValue, byteArray, sizeof(int));
    return intValue;
}

float Data_Store::bytesToFloat(byte *byteArray)
{
    float floatValue;
    memcpy(&floatValue, byteArray, sizeof(float));
    return floatValue;
}

void Data_Store::load()
{
    if (Data_Store::hasStoredData())
    {
        Data_Store::mem_address = DATA_STORE_DATA_ITEMS_ADDRESS;
        byte data_store_type = EEPROM.read(Data_Store::mem_address);
        Serial.println("data_store_type");
        Serial.println(data_store_type);
    }
    else
    {
    }
}
