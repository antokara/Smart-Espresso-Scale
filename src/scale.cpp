#include <scale.h>

NAU7802 scale;

/**
 * @author Antonios Karagiannis (antokarag@gmail.com)
 * @brief Scale
 * @date 2024-01-23
 *
 * @copyright Copyright (c) 2024
 *
 */
/**
 * @brief should be called once, from the main setup() function
 *
 */
void Scale::setup()
{
    Serial.println("Scale::setup - start");

    Wire1.setSDA(D2);
    Wire1.setSCL(D3);
    Wire1.begin();
    Wire1.setClock(400000); // We can increase I2C clock speed to 400kHz, the NAU7802 supports it

    if (scale.begin(Wire1) == false)
    {
        Serial.println("Scale::setup - Scale not detected. Please check wiring!");
        // TODO: show in screen
    }

    Serial.println("Scale::setup - end");
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