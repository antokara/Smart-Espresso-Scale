#include "services/data_store.h"

bool Data_Store::pendingSave = false;
unsigned int Data_Store::mem_address = EEPROM_HAS_STORED_DATA_FLAG_ADDRESS;

/**
 * @brief must be called before all other services,
 *        so that they can use it
 *
 */
void Data_Store::setup()
{
    EEPROM.begin(EEPROM_SIZE_BYTES);
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
    byte hasStoredData = EEPROM.read(EEPROM_HAS_STORED_DATA_FLAG_ADDRESS);
    byte hasStoredDataVersion = EEPROM.read(EEPROM_HAS_STORED_DATA_FLAG_ADDRESS + 1);
    return hasStoredData == EEPROM_HAS_STORED_DATA_FLAG_VALUE && hasStoredDataVersion == EEPROM_HAS_STORED_DATA_VER_VALUE;
}

/**
 * @brief converts a number to a byte array
 *
 * @param value can be int/float/double/etc.
 * @param byteArray
 */
template <typename T>
void Data_Store::numberToBytes(T value, byte *byteArray)
{
    memcpy(byteArray, &value, sizeof(value));
}

/**
 * @brief commits to memory all the set data
 *
 * @return true
 * @return false
 */
bool Data_Store::save()
{
    // makes the save
    return false;
}

void Data_Store::setIntData(int value)
{
    Serial.print("setIntData ");
    Serial.println(value);
    byte bytes[sizeof(value)];
    Data_Store::numberToBytes(value, bytes);
    for (int i = 0; i < sizeof(value); i++)
    {
        Serial.print(i);
        Serial.print(": ");
        Serial.println(bytes[i], HEX);
    }

    int cv = Data_Store::bytesToInt(bytes);
    Serial.print("cv int: ");
    Serial.println(cv);
}

void Data_Store::setFloatData(float value)
{
    Serial.print("setFloatData ");
    Serial.println(value);
    byte bytes[sizeof(value)];
    Data_Store::numberToBytes(value, bytes);
    for (int i = 0; i < sizeof(value); i++)
    {
        Serial.print(i);
        Serial.print(": ");
        Serial.println(bytes[i], HEX);
    }

    float cv = Data_Store::bytesToFloat(bytes);
    Serial.print("cv float: ");
    Serial.println(cv);
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
