/**
 * @author Antonios Karagiannis (antokarag@gmail.com)
 * @brief Scale
 * @date 2024-01-23
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <scale.h>

// the actual scale library instance
NAU7802 scale;

/**
 * @brief should be called once, from the main setup() function
 *
 */
void Scale::setup()
{
#ifdef SERIAL_DEBUG
    Serial.println("Scale::setup - start");
#endif
    Wire1.setSDA(SCALE_SDA_PIN);
    Wire1.setSCL(SCALE_SCL_PIN);
    Wire1.begin();
    Wire1.setClock(SCALE_I2C_CLOCK_HZ);

    if (scale.begin(Wire1) == false)
    {
#ifdef SERIAL_DEBUG
        Serial.println("Scale::setup - Scale not detected. Please check wiring!");
#endif
        // TODO: show in screen
    }
#ifdef SERIAL_DEBUG
    Serial.println("Scale::setup - end");
#endif
}

/**
 * @brief should be called on every iteration of the main loop() function
 *
 */
void Scale::loop()
{
    if (scale.available() == true)
    {
        long currentReading = scale.getReading();
        Serial.print("Reading: ");
        Serial.println(currentReading);
    }
}