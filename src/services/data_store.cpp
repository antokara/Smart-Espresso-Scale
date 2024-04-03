#include "services/data_store.h"

bool Data_Store::pendingSave = false;
bool Data_Store::pendingLoad = false;
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

    // calculate the number of bytes we will need and write it
    int data_length = sizeof(byteArray) / sizeof(byteArray[0]);
    byte data_length_byteArray[sizeof(data_length)];
    Data_Store::convertToBytes(data_length, data_length_byteArray);
    Data_Store::writeByteArray(data_length_byteArray);

    // write the actual data
    Data_Store::writeByteArray(byteArray);
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

void Data_Store::readBytes(int data_length, byte *byteArray)
{
    for (int i = 0; i < data_length; i++)
    {
        byteArray[i] = EEPROM.read(Data_Store::mem_address++);
    }
}

/**
 * @brief
 *
 * @param expected_type
 * @param byteArray
 * @return int data length or 0
 */
int Data_Store::readData(data_store_types expected_type, byte *byteArray)
{
    if (!Data_Store::pendingLoad && Data_Store::hasStoredData())
    {
        Data_Store::mem_address = DATA_STORE_DATA_ITEMS_ADDRESS;
        Data_Store::pendingLoad = true;
    }
    if (Data_Store::pendingLoad)
    {
        // read the data type and validate
        byte data_type = EEPROM.read(Data_Store::mem_address++);
        if (data_type != expected_type)
        {
#ifdef SERIAL_DEBUG
            Serial.print("ERROR! load data item type: ");
            Serial.print(data_type);
            Serial.print(", does not match the expected type: ");
            Serial.println(expected_type);
#endif
            return false;
        }

        // read the data length
        byte data_length_byteArray[sizeof(int)];
        Data_Store::readBytes(sizeof(int), data_length_byteArray);
        int data_length = Data_Store::bytesToInt(data_length_byteArray);

        // read the data
        Data_Store::readBytes(data_length, byteArray);

        // check if there are more data items
        byte next_flag = EEPROM.read(Data_Store::mem_address++);
        // when there are not, reset the flag...
        if (next_flag == data_store_next_flag_end)
        {
            Data_Store::pendingLoad = false;
        }

        return data_length;
    }

    return 0;
}

byte Data_Store::readByteData()
{
    byte byteArray[1];
    if (Data_Store::readData(data_store_type_byte, byteArray))
    {
        return byteArray[0];
    }
    return 0;
}

bool Data_Store::readBoolData()
{
    byte byteArray[1];
    if (Data_Store::readData(data_store_type_bool, byteArray))
    {
        return byteArray[0];
    }
    return false;
}

char Data_Store::readCharData()
{
    byte byteArray[1];
    if (Data_Store::readData(data_store_type_char, byteArray))
    {
        return (char)byteArray[0];
    }
    return ' ';
}

int Data_Store::readIntData()
{
    byte byteArray[sizeof(int)];
    if (Data_Store::readData(data_store_type_int, byteArray))
    {
        return Data_Store::bytesToInt(byteArray);
    }
    return 0;
}

float Data_Store::readFloatData()
{
    byte byteArray[sizeof(float)];
    if (Data_Store::readData(data_store_type_float, byteArray))
    {
        return Data_Store::bytesToFloat(byteArray);
    }
    return 0;
}

String Data_Store::readStringData()
{
    byte byteArray[DATA_STORE_MAX_STRING_LENGTH + 1];
    int data_length = Data_Store::readData(data_store_type_string, byteArray);
    if (data_length > 0)
    {
        String result = "";
        for (int i = 0; i < data_length; i++)
        {
            result += (char)byteArray[i];
        }
        return result;
    }
    return "";
}
